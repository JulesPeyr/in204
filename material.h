#ifndef MATERIALH
#define MATERIALH

#include "camera.h"
#include "string.h"

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
    virtual std::string name() const = 0; // Méthode pour obtenir le nom du matériau
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
    virtual std::string name() const override { return "matte"; } // Retourne le nom du matériau
    Rvector attenuation;
};

class metal : public material {
public:
    metal(const Rvector& a, float f) : attenuation(a) {
        if (f<1) fuzz = f; else fuzz = 1;
    }
    virtual bool scatter(const ray& r_in, const hit_record& rec, Rvector& att, ray& scattered) const {
        Rvector unit_direction = r_in.direction();
        unit_direction.make_unit_vector();
        Rvector reflected = reflect(unit_direction, rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        att = attenuation;
        return(dot(scattered.direction(), rec.normal)>0);
    }
    virtual std::string name() const override { return "metal"; } // Retourne le nom du matériau
    Rvector attenuation;
    float fuzz;
};

#endif