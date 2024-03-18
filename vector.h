#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>
#include <stdlib.h>
#include <iostream>


template <typename T> 
class vector {
    public:

        vector() {}
        vector(T c0, T c1, T c2) {c[0]=c0;c[1]=c1; c[2]=c2;}

        inline float x() const {return c[0];}
        inline float y() const {return c[1];}
        inline float z() const {return c[2];}
        inline float r() const {return c[0];}
        inline float g() const {return c[1];}
        inline float b() const {return c[2];}

        inline const vector<T>& operator+() const {return *this;}
        inline vector<T> operator-() const {return vector(-c[0],-c[1],-c[2]);}
        inline float operator[](int i) const {return c[i];}
        inline float& operator[](int i) {return c[i];}

        inline vector<T> operator+=(const vector<T> &v2);
        inline vector<T> operator-=(const vector<T> &v2);
        inline vector<T> operator*=(const vector<T> &v2);
        inline vector<T> operator/=(const vector<T> &v2);
        inline vector<T> operator*=(const float t);
        inline vector<T> operator/=(const float t);

        inline float norm() const {return sqrt(c[0]*c[0]+ c[1]*c[1] + c[2]*c[2]);}
        inline void make_unit_vector();
    
        T c[3];
};

template <typename T> 
inline std::istream& operator>>(std::istream &is, vector<T> &t){
    is >> t.c[0] >> t.c[1] >> t.c[2];
    return is; 
}

template <typename T> 
inline std::ostream& operator<<(std::ostream &os, vector<T> &t) {
 os << t.c[0] << " " << t.c[1] << " " << t.c[2];
 return os;
}

template <typename T> 
inline void vector<T>::make_unit_vector(){
    float k = 1.0/norm();
    c[0]*=k;c[1]*=k;c[2]*=k;
}

template <typename T> 
inline vector<T> operator+(const vector<T> &v1, const vector<T> &v2) {
 return vector(v1.c[0]+v2.c[0],v1.c[1]+v2.c[1],v1.c[2]+v2.c[2]);
}
template <typename T> 
inline vector<T> operator-(const vector<T> &v1, const vector<T> &v2) {
 return vector(v1.c[0]-v2.c[0],v1.c[1]-v2.c[1],v1.c[2]-v2.c[2]);
}
template <typename T> 
inline vector<T> operator*(const vector<T> &v1, const vector<T> &v2) {
 return vector<T>(v1.c[0]*v2.c[0],v1.c[1]*v2.c[1],v1.c[2]*v2.c[2]);
}
template <typename T> 
inline vector<T> operator/(const vector<T> &v1, const vector<T> &v2) {
 return vector(v1.c[0]/v2.c[0],v1.c[1]/v2.c[1],v1.c[2]/v2.c[2]);
}
template <typename T> 
inline vector<T> operator*(float t, const vector<T> &v) {
 return vector(t*v.c[0],t*v.c[1],t*v.c[2]);
}
template <typename T> 
inline vector<T> operator/(float t, const vector<T> &v) {
 return vector(t/v.c[0],t/v.c[1],t/v.c[2]);
}
template <typename T> 
inline vector<T> operator/(const vector<T> &v, float t) {
 return vector(v.c[0]/t,v.c[1]/t,v.c[2]/t);
}

template <typename T> 
inline float dot(const vector<T> &v1, const vector<T> &v2) {
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

template <typename T> 
inline vector<T> cross(const vector<T> &v1, const vector<T> &v2) {
	return vector(v1.c[1]*v2.c[2] - v1.c[2]*v2[1], 
	-(v1.c[0]*v2.c[2] - v1.c[2]*v2[0]), 
	v1.c[0]*v2.c[1] - v1.c[1]*v2[0]);
}

template <typename T> 
inline vector<T> vector<T>::operator+=(const vector<T> &v) {
 c[0] += v.c[0];
 c[1] += v.c[1];
 c[2] += v.c[2];
 return *this;
}
template <typename T> inline vector<T> vector<T>::operator-=(const vector<T> &v) {
 c[0] -= v.c[0];
 c[1] -= v.c[1];
 c[2] -= v.c[2];
 return *this;
}
template <typename T> inline vector<T> vector<T>::operator*=(const vector<T> &v) {
 c[0] *= v.c[0];
 c[1] *= v.c[1];
 c[2] *= v.c[2];
 return *this;
}
template <typename T> inline vector<T> vector<T>::operator/=(const vector<T> &v) {
 c[0] /= v.c[0];
 c[1] /= v.c[1];
 c[2] /= v.c[2];
 return *this;
}
template <typename T> inline vector<T> vector<T>::operator*=(const float t) {
 c[0] *= t;
 c[1] *= t;
 c[2] *= t;
 return *this;
}
template <typename T> inline vector<T> vector<T>::operator/=(const float t) {
 float k = 1.0/t;
 c[0] /= k;
 c[1] /= k;
 c[2] /= k;
 return *this;
}

template <typename T> inline vector<T> unit_vector(vector<T> v){
    return v/v.norm();
}


typedef vector<float> Rvector;
typedef vector<int> color;

#endif
