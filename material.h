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

bool refract(const Rvector& v,  const Rvector& n, float ni_over_nt, Rvector& refracted) {
    Rvector uv = v;
    uv.make_unit_vector();
    float dt = dot(uv,n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - dt*n) - sqrt(discriminant)*n;
        return true; 
    }
    else {return false;}
}

float schlick(float cosine, float ref_idx){ /*approximation polynomiale de la variation de réflexivité en fonction de l'angle pour les matériaux diélectriques*/
    float r0= (1-ref_idx)/(1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1+cosine),5);
}

class material {
public:
	std::string tag;
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

class dielectric : public material {
    public:
    dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, Rvector& attenuation, ray& scattered) const {
        Rvector outward_normal;
        Rvector reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = Rvector(1.0,1.0,0.0);
        Rvector refracted;
        float reflect_prob;
        float cosine;
        if(dot(r_in.direction(),rec.normal)>0){
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) /r_in.direction().norm();
        }
        else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0/ ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) /r_in.direction().norm();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine,ref_idx);
        }
        else {
            scattered = ray(rec.p, reflected);
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob){
            scattered = ray(rec.p,reflected);
        }
        else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }
    virtual std::string name() const override { return "diélectrique"; }


    float ref_idx;
};
#endif
