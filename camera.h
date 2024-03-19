#ifndef CAMERAH
#define CAMERAH

#include "objects.h"

class camera {
    public:
    camera(){
        lower_left_corner = Rvector(-2.0,-1.0,-1.0);
        horizontal = Rvector(4.0,0.0,0.0);
        vertical = Rvector(0.0,2.0,0.0);
        origin = Rvector(0.0,0.0,0.0);
    }

    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);}

    Rvector origin;
    Rvector lower_left_corner;
    Rvector horizontal;
    Rvector vertical;

};



#endif