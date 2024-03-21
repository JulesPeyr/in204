#ifndef DRAWING_H
#define DRAWING_H

#include <iostream>
#include <fstream>
#include "material.h"
#include <thread>
#include <vector>
#include <mutex>
#include "chrono.h"
std::mutex mtx;
using namespace std;

Rvector couleur(const ray& r, hitable* world, int depth){
    hit_record rec; 
    if(world->hit(r,0.001,MAXFLOAT,rec)){ 
        ray scattered;
        Rvector attenuation;
        if (depth < 50 && rec.mat_ptr && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
            return attenuation*couleur(scattered,world,depth+1);
        }
        else{
            return Rvector(0,0,0);
        }        
    }
    else {
        Rvector unit_direction = r.direction();
        unit_direction.make_unit_vector();
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Rvector(1.0, 1.0, 1.0) + t * Rvector(0.5, 0.7, 1.0);
    }
    
}

class drawing {
	public:
		//constructors
		drawing() {}
		drawing(const int l, const int h) {
			length=l;
			height=h;
			canvas=new unsigned int [l*h];
			//init with a white canvas
			for(int i=0; i<l; i++) {
				for(int j=0; j<h; j++) {
					canvas[i+j*length]=0xFFFFFF;
				}
			}
		}

		//destructor
		~drawing() {
			delete[] canvas;
		}
		
		//methods
		inline void draw_pixel(int, int, color);
		void renderLine(int start_y, int end_y, int width, int ns, camera& cam, hitable* world);
		void draw_image(const char *);
		void draw_image_multithreaded(const char *name_file, int num_threads, int ns, camera& cam, hitable* world);
		void print_image();
		inline unsigned int rgb_to_int(color);
		inline unsigned char int_to_r(unsigned int);
		inline unsigned char int_to_g(unsigned int);
		inline unsigned char int_to_b(unsigned int);

		//size of the canvas
		int length,height;
		//storing image data, to access the color of pixel (i,j) we access canvas[i+j*l], the origin is in the bottom left corner.
		unsigned int *canvas;
};

//we store the three rgb values as a single int
inline unsigned int drawing::rgb_to_int(color c) {
	return((c.r()<<16)+(c.g()<<8)+c.b());
}

inline unsigned char drawing::int_to_r(unsigned int rgb) {
	return((unsigned char)(rgb>>16));
}

inline unsigned char drawing::int_to_g(unsigned int rgb) {
	return((unsigned char)((rgb&0xff00)>>8));
}

inline unsigned char drawing::int_to_b(unsigned int rgb) {
	return((unsigned char)(rgb&0xff));
}

inline void drawing::draw_pixel(int x, int y, color c) {
	canvas[x+(height-y-1)*length]=rgb_to_int(c);
}


void drawing::draw_image(const char *name_file) {
	cout << "Writing a new image ! name of the file : " << name_file << "\n";
	Timer timer;
	ofstream file;
	file.open(name_file);
	//writing to the file...
	file << "P3\n" << length << " " << height << "\n255\n";
	for(int j=0; j<height; j++) {
		for(int i=0; i<length; i++) {
			int px_c = canvas[i+j*length];
			int px_r = int_to_r(px_c);
			int px_g = int_to_g(px_c);
			int px_b = int_to_b(px_c);
			file << px_r << " " << px_g << " " << px_b << endl;
		}
	}
	//closing file
	file.close();
}

void drawing::print_image() {
	cout << "P3\n" << length << " " << height << "\n255\n";
	for(int j=0; j<height; j++) {
		for(int i=0; i<length; i++) {
			int px_c = canvas[i+j*length];
			int px_r = int_to_r(px_c);
			int px_g = int_to_g(px_c);
			int px_b = int_to_b(px_c);
			cout << px_r << " " << px_g << " " << px_b << endl;
		}
	}
}

void drawing::renderLine(int start_y, int end_y, int width, int ns, camera& cam, hitable* world) { /*pour le multithread*/
    for (int y = start_y; y < end_y; ++y) {
        for (int x = 0; x < width; ++x) {
            // Rendu de pixel pour la ligne y
            // Utilisez les méthodes de drawing pour dessiner le pixel
			Rvector col(0,0,0);
            for(int s=0; s<ns; s++){
                float u = float(x + drand48()) / float(width);         
                float v = float(y + drand48()) / float(height);
                ray r = cam.get_ray(u,v);
                Rvector p = r.point_at_parameter(2.0);
                col += couleur(r,world,0);
            }

            col /= float(ns);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
			draw_pixel(x, y, color(ir, ig, ib));
        }
    }
}
void drawing::draw_image_multithreaded(const char *name_file, int num_threads, int ns, camera& cam, hitable* world) {
    cout << "Writing a new image! File name: " << name_file << "\n";
	
	Timer timer;

	//barre de progression
	int sum=0;

    // Créer une barrière pour synchroniser les threads
    std::mutex mutex;

    ofstream file;
    file.open(name_file);

    // Écrire l'en-tête de l'image dans le fichier
    file << "P3\n" << length << " " << height << "\n255\n";

    cout << endl;

    // Créer les threads pour le rendu de l'image
    vector<thread> threads;
    int rows_per_thread = height / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start_y = i * rows_per_thread;
        int end_y = (i == num_threads - 1) ? height : (i + 1) * rows_per_thread;
        threads.emplace_back([&](int start, int end) {
            for (int y = start; y < end; ++y) {
	    	sum++;
		if(((100*sum)/height)%5==0)
			cout << "\b\b\b\b" << 100*sum/height << "%";
			flush(cout);
                for (int x = 0; x < length; ++x) {
                    Rvector col(0,0,0);
                    for(int s=0; s<ns; s++){
                        float u = float(x + drand48()) / float(length);         
                        float v = float(y + drand48()) / float(height);
                        ray r = cam.get_ray(u,v);
                        Rvector p = r.point_at_parameter(2.0);
                        col += couleur(r,world,0);
                    }
                    col /= float(ns);
                    int ir = int(255.99*col.r());
                    int ig = int(255.99*col.g());
                    int ib = int(255.99*col.b());
                    // Verrouiller l'accès à la matrice canvas pour éviter les conflits
                    mutex.lock();
                    draw_pixel(x, y, color(ir, ig, ib));
                    mutex.unlock();
                }
            }
        }, start_y, end_y);
    }

    // Attendre que tous les threads aient terminé
    for (auto& t : threads) {
        t.join();
    }

    // Écrire les données d'image depuis la matrice canvas dans le fichier
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < length; i++) {
            int px_c = canvas[i + j * length];
            int px_r = int_to_r(px_c);
            int px_g = int_to_g(px_c);
            int px_b = int_to_b(px_c);
            file << px_r << " " << px_g << " " << px_b << endl;
        }
    }

    cout << endl;

    // Fermer le fichier
    file.close();
}
#endif
