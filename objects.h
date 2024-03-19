#ifndef OBJECTS_H
#define OBJECTS_H

#include "hitable.h"
class material;
class sphere: public hitable{
    public:
        sphere() {}
        sphere(Rvector cen,float r, material* mat) : center(cen), radius(r), mat_ptr(mat) {};
        virtual bool hit(const ray& r, float t_min,float t_max, hit_record& rec) const;
        material* get_material() const {return mat_ptr;}
        
        Rvector center;
        float radius;
        material* mat_ptr;

};
bool sphere::hit(const ray& r, float t_min, float t_max,hit_record& rec) const { /* définit la hitbox d'une sphère et si le rayon r la percute*/
    Rvector oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = dot(oc,r.direction());
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant>0){
        float temp = (-b - sqrt(b*b-a*c))/a;
        if (temp< t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif
