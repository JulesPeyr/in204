#include <iostream>
   /* biblitothèque qui va nous permettre de "dessiner" sur un écran, template qui facilite son utilisation*/
#include "material.h"
#include "float.h"
#include "drawing.h"






hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n+1];
	list[0] = new sphere(Rvector(0,-1000,0),1000,new matte(Rvector(0.5,0.5,0.5)));
	int i = 1;
	for(int a=-11;a<11;a++) {
		for(int b=-11;b<11;b++) {
			float choose_mat = drand48();
			Rvector center(a+0.9*drand48(),0.2,b+0.9*drand48());
			if(choose_mat < 0.8) {
				list[i++] = new sphere(center, 0.2, new matte(Rvector(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
			} else if(choose_mat < 0.95) {
				list[i++] = new sphere(center, 0.2, new metal(Rvector(0.5*(1+drand48()),0.5*(1+drand48()),0.5*(1+drand48())),0.5*drand48()));
			} else {
				list[i++] = new sphere(center, 0.2, new dielectric(1.5));
			}
			
		}
	}
	list[i++] = new sphere(Rvector(0,1,0), 1, new dielectric(1.5));
	list[i++] = new sphere(Rvector(-4,1,0), 1, new matte(Rvector(.4,.2,.1)));
	list[i++] = new sphere(Rvector(4,1,0), 1, new metal(Rvector(.7,.6,.5),0));
	return new hitable_list(list,i);
}

int main(){
    int width = 1980;
    int height = 1080;
    int ns = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";   /* headers du fichier ppm, format d'image assez intuitif*/
    /*hitable* list[4];                           
    list[0] = new sphere(Rvector(0,0,-1),0.5, new matte(Rvector(0.8,0.1,0.1)));    /* petite boule
    list[1] = new sphere(Rvector(0,-100.5,-1),100, new matte(Rvector(0.8,0.1,0.1)));
    list[2] = new sphere(Rvector(1,0,-1),0.5, new dielectric(1.5));
    list[3] = new sphere(Rvector(1,0,1),0.5, new dielectric(1.5));
    */
    hitable* world = random_scene();
    Rvector lookfrom(13.0,2.0,3.0);
	Rvector lookat(0,0,0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
    camera cam(lookfrom,lookat,Rvector(0,1,0),20, float(width)/float(height));
    drawing img(width, height);
    int max_threads = thread::hardware_concurrency();
    img.draw_image_multithreaded("output_image.ppm", max_threads, ns, cam, world);
    
}