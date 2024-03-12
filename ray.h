#include "vector.h"

class ray{
    public:
        ray() {}
        ray(const vector& a, const vector& b) { A = a; B = b;}
        vector origin() const {return A;}
        vector direction() const {return B;}
        vector point_at_parameter(float t) const {return A + t*B;}

        vector A;
        vector B;
};