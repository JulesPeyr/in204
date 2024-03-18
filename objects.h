#ifndef OBJECTS_H
#define OBJECTS_H

#include "hitable.h"

class sphere: public hitable{
    public:
        sphere() {}
        sphere(vector cen,float r) : center(cen), radius(r) {};
        virtual bool hit(const ray& r, float t_min,float t_max, hit_record& rec) const;
        vector center;
        float radius;

};
bool sphere::hit(const ray& r, float t_min, float t_max,hit_record& rec) const { /* définit la hitbox d'une sphère et si le rayon r la percute*/
    vector oc = r.origin()-center;
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
