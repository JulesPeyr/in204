#include <iostream>
   /* biblitothèque qui va nous permettre de "dessiner" sur un écran, template qui facilite son utilisation*/
#include "objects.h"
#include "float.h"





Rvector couleur(const ray& r, hitable* world){
    hit_record rec; 
    if(world->hit(r,0.0,MAXFLOAT,rec)){ /* si le rayon touche la sphère c'est un maxi dégradé en fonction de la normale*/
        return 0.5*vector(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }
    Rvector unit_direction = r.direction();
    unit_direction.make_unit_vector();
    float t = 0.5*(unit_direction.y() + 1.0);  /*sinon le dégradé de bleu*/
    return (1.0-t)*Rvector(1.0,1.0,1.0) + t*Rvector(0.5,0.7,1.0);
}

int main(){
    int width = 800;
    int height = 400;
    std::cout << "P3\n" << width << " " << height << "\n255\n";   /* headers du fichier ppm, format d'image assez intuitif*/
    Rvector lower_left_corner(-2.0,-1.0,-1.0);
    Rvector horizontal(4.0,0.0,0.0);
    Rvector vertical(0.0,2.0,0.0);
    Rvector origin(0.0,0.0,0.0);
    hitable* list[2];                           /*on a donc sur l'image deux boules*/
    list[0] = new sphere(Rvector(0,0,-1),0.5);    /* petite boule*/
    list[1] = new sphere(Rvector(0,-100.5,-1),100);  /* grosse boule*/
    hitable* world = new hitable_list(list,2);
    for(int y = height-1; y>=00; y--) {
        for(int x=0; x<width; x++){
            float u = float(x) / float(width);
            float v = float(y) / float(height);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vector col = couleur(r,world);
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";

        }

    }    
}