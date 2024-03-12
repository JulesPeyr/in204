#include "ray.h"

bool hit_sphere(const vector center, float radius, const ray& r){ /* définit la hitbox d'une sphère et si le rayon r la percute*/
    vector oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = 2.0*dot(oc,r.direction());
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant>0);
}