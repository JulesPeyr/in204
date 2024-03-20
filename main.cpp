#include <iostream>
   /* biblitothèque qui va nous permettre de "dessiner" sur un écran, template qui facilite son utilisation*/
#include "material.h"
#include "float.h"





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

int main(){
    int width = 800;
    int height = 400;
    int ns = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";   /* headers du fichier ppm, format d'image assez intuitif*/
    hitable* list[4];                           
    list[0] = new sphere(Rvector(0,0,-1),0.5, new matte(Rvector(0.8,0.1,0.1)));    /* petite boule*/
    list[1] = new sphere(Rvector(0,-100.5,-1),100, new matte(Rvector(0.8,0.8,0.0)));
    list[2] = new sphere(Rvector(1,0,-1),0.5, new metal(Rvector(0.8,0.6,0.2),0.3));
    list[3] = new sphere(Rvector(1,0,-1),0.5, new metal(Rvector(0.8,0.8,0.8),1));
    
    hitable* world = new hitable_list(list,4);
    camera cam;
    for(int y = height-1; y>=00; y--) {
        for(int x=0; x<width; x++){                                     /* implémentation de l'antialiasing, on fait la moyenne des pixels sur les bords*/
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
            std::cout << ir << " " << ig << " " << ib << "\n";

        }

    }    
}