#ifndef MATERIALH
#define MATERIALH

#include "camera.h"

Rvector random_in_unit_sphere(){                                            
    Rvector p;
    do {
        p = 2.0*Rvector(drand48(),drand48(),drand48()) - Rvector(1,1,1);
    } while(p.norm()*p.norm() >= 1.0);
    return p;
}

Rvector reflect(const Rvector& v, const Rvector& n){    /*réflexion sur une surface métallique*/
    return v - 2*dot(v,n)*n;
}

class material {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, Rvector& attenuation, ray& scattered) const = 0;
};

class matte : public material {
    public:
        matte(const Rvector& a) : attenuation(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, Rvector& att, ray& scattered) const {
            Rvector target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p, target-rec.p);
            att = attenuation;
            return true;
        }
        Rvector attenuation;
};

class metal : public material {
    public:
        metal(const Rvector& a) : attenuation(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, Rvector& att, ray& scattered) const {
            Rvector unit_direction = r_in.direction();
            unit_direction.make_unit_vector();
            Rvector reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            att = attenuation;
            return(dot(scattered.direction(), rec.normal)>0);
        }
        Rvector attenuation;
};

#endif