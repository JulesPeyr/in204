#include <math.h>
#include <stdlib.h>
#include <iostream>

class vector {
    public:

        vector() {}
        vector(float c0, float c1, float c2) {c[0]=c0;c[1]=c1; c[2]=c2;}

        inline float x() const {return c[0];}
        inline float y() const {return c[1];}
        inline float z() const {return c[2];}
        inline float r() const {return c[0];}
        inline float g() const {return c[1];}
        inline float b() const {return c[2];}

        inline const vector& operator+() const {return *this;}
        inline vector operator-() const {return vector(-c[0],-c[1],-c[2]);}
        inline float operator[](int i) const {return c[i];}
        inline float& operator[](int i) {return c[i];}

        inline vector& operator+=(const vector &v2);
        inline vector& operator-=(const vector &v2);
        inline vector& operator*=(const vector &v2);
        inline vector& operator/=(const vector &v2);
        inline vector& operator*=(const float t);
        inline vector& operator/=(const float t);

        inline float norm() const {return sqrt(c[0]*c[0]+ c[1]*c[1] + c[2]*c[2]);}
        inline void make_unit_vector();

    
        float c[3];
};

inline std::istream& operator>>(std::istream &is, vector &t){
    is >> t.c[0] >> t.c[1] >> t.c[2];
    return is; 
}

inline std::ostream& operator<<(std::ostream &os, vector &t) {
 os << t.c[0] << " " << t.c[1] << " " << t.c[2];
 return os;
}

inline void vector::make_unit_vector(){
    float k = 1.0/norm();
    c[0]*=k;c[1]*=k;c[2]*=k;
}

inline vector operator+(const vector &v1, const vector &v2) {
 return vector(v1.c[0]+v2.c[0],v1.c[1]+v2.c[1],v1.c[2]+v2.c[2]);
}
inline vector operator-(const vector &v1, const vector &v2) {
 return vector(v1.c[0]-v2.c[0],v1.c[1]-v2.c[1],v1.c[2]-v2.c[2]);
}
inline vector operator*(const vector &v1, const vector &v2) {
 return vector(v1.c[0]*v2.c[0],v1.c[1]*v2.c[1],v1.c[2]*v2.c[2]);
}
inline vector operator/(const vector &v1, const vector &v2) {
 return vector(v1.c[0]/v2.c[0],v1.c[1]/v2.c[1],v1.c[2]/v2.c[2]);
}
inline vector operator*(float t, const vector &v) {
 return vector(t*v.c[0],t*v.c[1],t*v.c[2]);
}
inline vector operator/(float t, const vector &v) {
 return vector(t/v.c[0],t/v.c[1],t/v.c[2]);
}
inline vector operator/(const vector &v, float t) {
 return vector(v.c[0]/t,v.c[1]/t,v.c[2]/t);
}

inline float dot(const vector &v1, const vector &v2) {
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline vector cross(const vector &v1, const vector &v2) {
	return vector(v1.c[1]*v2.c[2] - v1.c[2]*v2[1], 
	-(v1.c[0]*v2.c[2] - v1.c[2]*v2[0]), 
	v1.c[0]*v2.c[1] - v1.c[1]*v2[0]);
}

inline vector& vector::operator+=(const vector &v) {
 c[0] += v.c[0];
 c[1] += v.c[1];
 c[2] += v.c[2];
 return *this;
}
inline vector& vector::operator-=(const vector &v) {
 c[0] -= v.c[0];
 c[1] -= v.c[1];
 c[2] -= v.c[2];
 return *this;
}
inline vector& vector::operator*=(const vector &v) {
 c[0] *= v.c[0];
 c[1] *= v.c[1];
 c[2] *= v.c[2];
 return *this;
}
inline vector& vector::operator/=(const vector &v) {
 c[0] /= v.c[0];
 c[1] /= v.c[1];
 c[2] /= v.c[2];
 return *this;
}
inline vector& vector::operator*=(const float t) {
 c[0] *= t;
 c[1] *= t;
 c[2] *= t;
 return *this;
}
inline vector& vector::operator/=(const float t) {
 float k = 1.0/t;
 c[0] /= k;
 c[1] /= k;
 c[2] /= k;
 return *this;
}

inline vector unit_vector(vector v){
    return v/v.norm();
}