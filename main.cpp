#include <iostream>
   /* biblitothèque qui va nous permettre de "dessiner" sur un écran, template qui facilite son utilisation*/
#include "camera.h"
#include "float.h"



Rvector random_in_unit_sphere(){
    Rvector p;
    do {
        p = 2.0*Rvector(drand48(),drand48(),drand48()) - Rvector(1,1,1);
    } while(p.norm()*p.norm() >= 1.0);
    return p;
}

Rvector couleur(const ray& r, hitable* world){
    hit_record rec; 
    if(world->hit(r,0.0,MAXFLOAT,rec)){ 
        Rvector target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*couleur( ray(rec.p,target-rec.p),world);
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
    hitable* list[2];                           /*on a donc sur l'image deux boules*/
    list[0] = new sphere(Rvector(0,0,-1),0.5);    /* petite boule*/
    list[1] = new sphere(Rvector(0,-100.5,-1),100);  /* grosse boule*/
    hitable* world = new hitable_list(list,2);
    camera cam;
    for(int y = height-1; y>=00; y--) {
        for(int x=0; x<width; x++){                                     /* implémentation de l'antialiasing, on fait la moyenne des pixels sur les bords*/
            Rvector col(0,0,0);
            for(int s=0; s<ns; s++){
                float u = float(x + drand48()) / float(width);         
                float v = float(y + drand48()) / float(height);
                ray r = cam.get_ray(u,v);
                Rvector p = r.point_at_parameter(2.0);
                col += couleur(r,world);
            }

            col /= float(ns);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";

        }

    }    
}