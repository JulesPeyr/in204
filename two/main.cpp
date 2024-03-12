#include <iostream>
#include "sdltemplate.h"    /* biblitothèque qui va nous permettre de "dessiner" sur un écran, template qui facilite son utilisation*/
#include "vector.h" /* classe permettant de gérer les vecteurs et les opérations associées*/

using namespace sdltemplate;
int main(){
    int width = 800;
    int height = 400;
    int delay = 3000;
    std::cout << "P3\n" << width << " " << height << "\n255\n";   /* headers du fichier ppm, format d'image assez intuitif*/
    sdl("RayTracer",width,height);
    loop();
    for(int y = height-1; y>=00; y--) {
        for(int x=0; x<width; x++){
            vector color(float(x) / float(width),float(y) /float (height), 0.4);
            int ir = int(255.99*color.r());
            int ig = int(255.99*color.g());
            int ib = int(255.99*color.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
            setDrawColor(createColor(ir,ig,ib,255));
            drawPoint(x,height-y);

        }

    }
    while (running)
    {
        loop();
    }
    
}