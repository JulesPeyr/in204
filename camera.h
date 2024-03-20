#ifndef CAMERAH
#define CAMERAH

#include "objects.h"
#include "ray.h"

class camera {
    public:
    camera(){}

    //fov (field of vision) is top to bottom in degrees
    camera(float fov, float aspect) {
	float theta=fov*M_PI/180;
	float half_height = tan(theta/2);
	float half_width = aspect * half_height;
	lower_left_corner = Rvector(-half_width, -half_height, -1.0);
	horizontal = Rvector(2*half_width,0.0,0.0);
	vertical = Rvector(0.0, 2*half_height, 0.0);
	origin = Rvector(0.0, 0.0, 0.0);
    }

    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);}

    Rvector origin{Rvector(0.0,0.0,0.0)};
    Rvector lower_left_corner{Rvector(-2.0,-1.0,-1.0)};
    Rvector horizontal{Rvector(4.0,0.0,0.0)};
    Rvector vertical{Rvector(0.0,2.0,0.0)};

};



#endif
