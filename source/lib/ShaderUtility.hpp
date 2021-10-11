#pragma once

#include "../../include/BaseInclude.hpp"

struct vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    vec4();
    vec4(const float f);
    vec4(const float x, const float y);
    vec4(const float x, const float y, const float z);
    vec4(const float x, const float y, const float z, const float w);
    vec4 SetAll(const float f);
    vec4 SetAll(const float x, const float y);
    vec4 SetAll(const float x, const float y, const float z);
    vec4 SetAll(const float x, const float y, const float z, const float w);
};

vec4 operator+(const vec4 l, const vec4 r);
vec4 operator+(const float l, const vec4 r);
vec4 operator+(const vec4 l, const float r);
vec4 operator-(const vec4 l, const vec4 r);
vec4 operator-(const float l, const vec4 r);
vec4 operator-(const vec4 l, const float r);
vec4 operator*(const vec4 l, const vec4 r);
vec4 operator*(const float l, const vec4 r);
vec4 operator*(const vec4 l, const float r);
vec4 operator/(const vec4 l, const vec4 r);
vec4 operator/(const float l, const vec4 r);
vec4 operator/(const vec4 l, const float r);
vec4 operator-(const vec4 l);
void operator+=(vec4 &l, const vec4 r);
void operator+=(vec4 &l, const float r);
void operator-=(vec4 &l, const vec4 r);
void operator-=(vec4 &l, const float r);
void operator*=(vec4 &l, const vec4 r);
void operator*=(vec4 &l, const float r);
void operator/=(vec4 &l, const vec4 r);
void operator/=(vec4 &l, const float r);
int operator==(const vec4 l, const vec4 r);
int operator!=(const vec4 l, const vec4 r);
std::ostream &operator<<(std::ostream &l, const vec4 &r);

template <typename T>
T radians(const T d);
template <typename T>
T degrees(const T r);
vec4 abs(const vec4 x);
vec4 sign(const vec4 x);
float sign(const float x);
vec4 floor(const vec4 x);
vec4 ceil(const vec4 x);
template <typename T>
T fract(const T x);
template <typename T>
T mod(const T x, const T y);
float min(const float x, const float y);
vec4 min(const vec4 x, const vec4 y);
float max(const float x, const float y);
vec4 max(const vec4 x, const vec4 y);
template <typename T>
T clamp(const T x, const T a, const T b);
template <typename T>
T mix(const T x, const T y, const T a);
float step(const float a, const float x);
vec4 step(const vec4 a, const vec4 x);
template <typename T>
T smoothstep(const T a, const T b, const T t);
vec4 sin(const vec4 x);
vec4 cos(const vec4 x);
vec4 tan(const vec4 x);
vec4 asin(const vec4 x);
vec4 acos(const vec4 x);
vec4 atan2(const vec4 y, const vec4 x);
vec4 pow(const vec4 x, const vec4 y);
vec4 exp(const vec4 x);
vec4 log(const vec4 x);
vec4 exp2(const vec4 x);
vec4 log2(const vec4 x);
vec4 sqrt(const vec4 x);
vec4 inverssqrt(const vec4 x);
float length(const vec4 x);
float distance(const vec4 x, const vec4 y);
vec4 normalize(const vec4 x);
float dot(const vec4 x, const vec4 y);
vec4 cross(const vec4 v1, const vec4 v2);
vec4 faceforward(const vec4 N, const vec4 I, const vec4 R);
vec4 reflect(const vec4 I, const vec4 N);
vec4 refract(const vec4 I, const vec4 N, const float eta);
vec4 lessThan(const vec4 x, const vec4 y);
vec4 lessThanEqual(const vec4 x, const vec4 y);
vec4 greaterThan(const vec4 x, const vec4 y);
vec4 greaterThanEqual(const vec4 x, const vec4 y);
vec4 equal(const vec4 x, const vec4 y);
vec4 notEqual(const vec4 x, const vec4 y);
float any(const vec4 x);
float all(const vec4 x);
vec4 _not(const vec4 x);
vec4 random2(const vec4 uv);
float gradationNoise(const vec4 uv);
vec4 mul4x4444(const vec4 x, const vec4 y[4]);
vec4 rotate(const vec4 uv, const float angle);
vec4 vecRotateX(const vec4 vec, const float angle);
vec4 vecRotateY(const vec4 vec, const float angle);
vec4 vecRotateZ(const vec4 vec, const float angle);
float gauss(const float a, const float x);
float lengthsqr(const vec4 x);
float roundN(const float num, const int n);
template <typename T>
T remap(const T v, const T inMin, const T inMax, const T outMin, const T outMax);
vec4 screenSynthesis(const vec4 def, const vec4 syn);
vec4 rainbow(const float v);