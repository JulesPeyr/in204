#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>
#include <stdlib.h>
#include <iostream>


template <typename T> 
class myVector {
    public:

        myVector() {}
        myVector(T c0, T c1, T c2) {c[0]=c0;c[1]=c1; c[2]=c2;}

        inline T x() const {return c[0];}
        inline T y() const {return c[1];}
        inline T z() const {return c[2];}
        inline T r() const {return c[0];}
        inline T g() const {return c[1];}
        inline T b() const {return c[2];}

        inline const myVector<T>& operator+() const {return *this;}
        inline myVector<T> operator-() const {return myVector(-c[0],-c[1],-c[2]);}
        inline float operator[](int i) const {return c[i];}
        inline float& operator[](int i) {return c[i];}

        inline myVector<T> operator+=(const myVector<T> &v2);
        inline myVector<T> operator-=(const myVector<T> &v2);
        inline myVector<T> operator*=(const myVector<T> &v2);
        inline myVector<T> operator/=(const myVector<T> &v2);
        inline myVector<T> operator*=(const float t);
        inline myVector<T> operator/=(const float t);

        inline float norm() const {return sqrt(c[0]*c[0]+ c[1]*c[1] + c[2]*c[2]);}
        inline void make_unit_myVector();
    
        T c[3];
};

template <typename T> 
inline std::istream& operator>>(std::istream &is, myVector<T> &t){
    is >> t.c[0] >> t.c[1] >> t.c[2];
    return is; 
}

template <typename T> 
inline std::ostream& operator<<(std::ostream &os, myVector<T> &t) {
 os << t.c[0] << " " << t.c[1] << " " << t.c[2];
 return os;
}

template <typename T> 
inline void myVector<T>::make_unit_myVector(){
    float k = 1.0/norm();
    c[0]*=k;c[1]*=k;c[2]*=k;
}

template <typename T> 
inline myVector<T> operator+(const myVector<T> &v1, const myVector<T> &v2) {
 return myVector(v1.c[0]+v2.c[0],v1.c[1]+v2.c[1],v1.c[2]+v2.c[2]);
}
template <typename T> 
inline myVector<T> operator-(const myVector<T> &v1, const myVector<T> &v2) {
 return myVector(v1.c[0]-v2.c[0],v1.c[1]-v2.c[1],v1.c[2]-v2.c[2]);
}
template <typename T> 
inline myVector<T> operator*(const myVector<T> &v1, const myVector<T> &v2) {
 return myVector<T>(v1.c[0]*v2.c[0],v1.c[1]*v2.c[1],v1.c[2]*v2.c[2]);
}
template <typename T> 
inline myVector<T> operator/(const myVector<T> &v1, const myVector<T> &v2) {
 return myVector(v1.c[0]/v2.c[0],v1.c[1]/v2.c[1],v1.c[2]/v2.c[2]);
}
template <typename T> 
inline myVector<T> operator*(float t, const myVector<T> &v) {
 return myVector(t*v.c[0],t*v.c[1],t*v.c[2]);
}
template <typename T> 
inline myVector<T> operator/(float t, const myVector<T> &v) {
 return myVector(t/v.c[0],t/v.c[1],t/v.c[2]);
}
template <typename T> 
inline myVector<T> operator/(const myVector<T> &v, float t) {
 return myVector(v.c[0]/t,v.c[1]/t,v.c[2]/t);
}

template <typename T> 
inline float dot(const myVector<T> &v1, const myVector<T> &v2) {
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

template <typename T> 
inline myVector<T> cross(const myVector<T> &v1, const myVector<T> &v2) {
	return myVector(v1.c[1]*v2.c[2] - v1.c[2]*v2[1], 
	-(v1.c[0]*v2.c[2] - v1.c[2]*v2[0]), 
	v1.c[0]*v2.c[1] - v1.c[1]*v2[0]);
}

template <typename T> 
inline myVector<T> myVector<T>::operator+=(const myVector<T> &v) {
 c[0] += v.c[0];
 c[1] += v.c[1];
 c[2] += v.c[2];
 return *this;
}
template <typename T> inline myVector<T> myVector<T>::operator-=(const myVector<T> &v) {
 c[0] -= v.c[0];
 c[1] -= v.c[1];
 c[2] -= v.c[2];
 return *this;
}
template <typename T> inline myVector<T> myVector<T>::operator*=(const myVector<T> &v) {
 c[0] *= v.c[0];
 c[1] *= v.c[1];
 c[2] *= v.c[2];
 return *this;
}
template <typename T> inline myVector<T> myVector<T>::operator/=(const myVector<T> &v) {
 c[0] /= v.c[0];
 c[1] /= v.c[1];
 c[2] /= v.c[2];
 return *this;
}
template <typename T> inline myVector<T> myVector<T>::operator*=(const float t) {
 c[0] *= t;
 c[1] *= t;
 c[2] *= t;
 return *this;
}
template <typename T> inline myVector<T> myVector<T>::operator/=(const float t) {
 float k = 1.0/t;
 c[0] *= k;
 c[1] *= k;
 c[2] *= k;
 return *this;
}

typedef myVector<float> Rvector;
typedef myVector<int> color;

#endif
