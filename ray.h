#ifndef RAY_H
#define RAY_H

#include "vector.h"

class ray{
    public:
        ray() {}
        ray(const Rvector& a, const Rvector& b) { A = a; B = b;}
        
        Rvector origin() const {return A;}
        Rvector direction() const {return B;}
        Rvector point_at_parameter(float t) const {return A + t*B;}

        Rvector A;
        Rvector B;
};

#endif
