#ifndef CAMERAH
#define CAMERAH

#include "objects.h"
#include "ray.h"

class camera {
    public:
    camera(){}

    //fov (field of vision) is top to bottom in degrees
    camera(Rvector lookfrom, Rvector lookat, Rvector vup, float fov, float aspect) {
	Rvector u, v, w;
	float theta=fov*M_PI/180;
	float half_height = tan(theta/2);
	float half_width = aspect * half_height;
	origin=lookfrom;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup,w));
	v=cross(w,u);
	lower_left_corner = origin - half_width*u - half_height*v - w;
	horizontal = 2*half_width*u;
	vertical = 2*half_height*v;
    }

    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);}

    Rvector origin{Rvector(0.0,0.0,0.0)};
    Rvector lower_left_corner{Rvector(-2.0,-1.0,-1.0)};
    Rvector horizontal{Rvector(4.0,0.0,0.0)};
    Rvector vertical{Rvector(0.0,2.0,0.0)};

};



#endif
