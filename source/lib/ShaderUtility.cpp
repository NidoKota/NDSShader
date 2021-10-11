#include "ShaderUtility.hpp"

//////////////////////以下GLSLとほぼ同じ関数//////////////////////

template float radians(const float d);
template vec4 radians(const vec4 d);
template <typename T>
T radians(const T d)
{
    return d / 360.f * 2.f * M_PI;
}

template float degrees(const float r);
template vec4 degrees(const vec4 r);
template <typename T>
T degrees(const T r)
{
    return r / 2.f / M_PI * 360.f;
}

vec4 abs(const vec4 x)
{
    return vec4(abs(x.x), abs(x.y), abs(x.z));
}

vec4 sign(const vec4 x)
{
    return vec4(sign(x.x), sign(x.y), sign(x.z));
}

float sign(const float x)
{
    return x > 0 ? 1.f : x < 0 ? -1.f
                               : 0.f;
}

//整数部分のみ取り出す
vec4 floor(const vec4 x)
{
    return vec4(floor(x.x), floor(x.y), floor(x.z));
}

//引数以上の最小の整数を返す
vec4 ceil(const vec4 x)
{
    return vec4(ceil(x.x), ceil(x.y), ceil(x.z));
}

template float fract(const float x);
template vec4 fract(const vec4 x);
//小数部分のみ取り出す
template <typename T>
T fract(const T x)
{
    return x - floor(x);
}

template float mod(const float x, const float y);
template vec4 mod(const vec4 x, const vec4 y);
//(x / y)の余り
template <typename T>
T mod(const T x, const T y)
{
    return x - y * floor(x / y);
}

float min(const float x, const float y)
{
    return x > y ? y : x;
}

vec4 min(const vec4 x, const vec4 y)
{
    return vec4(min(x.x, y.x), min(x.y, y.y), min(x.z, y.z));
}

float max(const float x, const float y)
{
    return x > y ? x : y;
}

vec4 max(const vec4 x, const vec4 y)
{
    return vec4(max(x.x, y.x), max(x.y, y.y), max(x.z, y.z));
}

template int clamp(const int x, const int a, const int b);
template float clamp(const float x, const float a, const float b);
template vec4 clamp(const vec4 x, const vec4 a, const vec4 b);
template <typename T>
T clamp(const T x, const T a, const T b)
{
    return min(max(x, a), b);
}

template float mix(const float x, const float y, const float a);
template vec4 mix(const vec4 x, const vec4 y, const vec4 a);
template <typename T>
T mix(const T x, const T y, const T a)
{
    return x * (1.f - a) + y * a;
}

float step(const float a, const float x)
{
    return a <= x;
}

vec4 step(const vec4 a, const vec4 x)
{
    return vec4(step(a.x, x.x), step(a.y, x.y), step(a.z, x.z));
}

template float smoothstep(const float a, const float b, const float t);
template vec4 smoothstep(const vec4 a, const vec4 b, const vec4 t);
//エルミート補完
template <typename T>
T smoothstep(const T a, const T b, const T t)
{
    T c = clamp((t - a) / (b - a), T(0.f), T(1.f));
    return c * c * (c * -2.f + 3.f);
}

vec4 sin(const vec4 x)
{
    return vec4(sin(x.x), sin(x.y), sin(x.z));
}

vec4 cos(const vec4 x)
{
    return vec4(cos(x.x), cos(x.y), cos(x.z));
}

vec4 tan(const vec4 x)
{
    return vec4(tan(x.x), tan(x.y), tan(x.z));
}

vec4 asin(const vec4 x)
{
    return vec4(asin(x.x), asin(x.y), asin(x.z));
}

vec4 acos(const vec4 x)
{
    return vec4(acos(x.x), acos(x.y), acos(x.z));
}

//GLSLの場合atan
vec4 atan2(const vec4 y, const vec4 x)
{
    return vec4(atan2(y.x, x.x), atan2(y.y, x.y), atan2(y.z, x.z));
}

vec4 pow(const vec4 x, const vec4 y)
{
    return vec4(pow(x.x, y.x), pow(x.y, y.y), pow(x.z, y.z));
}

vec4 exp(const vec4 x)
{
    return vec4(exp(x.x), exp(x.y), exp(x.z));
}

vec4 log(const vec4 x)
{
    return vec4(log(x.x), log(x.y), log(x.z));
}

vec4 exp2(const vec4 x)
{
    return vec4(exp2(x.x), exp2(x.y), exp2(x.z));
}

vec4 log2(const vec4 x)
{
    return vec4(log2(x.x), log2(x.y), log2(x.z));
}

vec4 sqrt(const vec4 x)
{
    return vec4(sqrt(x.x), sqrt(x.y), sqrt(x.z));
}

vec4 inverssqrt(const vec4 x)
{
    return vec4(1.f / sqrt(x.x), 1.f / sqrt(x.y), 1.f / sqrt(x.z));
}

float length(const vec4 x)
{
    return sqrt(lengthsqr(x));
}

float distance(const vec4 x, const vec4 y)
{
    return sqrt(lengthsqr(y - x));
}

vec4 normalize(const vec4 x)
{
    float mag = 1 / length(x);
    return x * mag;
}

//内積
float dot(const vec4 x, const vec4 y)
{
    return x.x * y.x + x.y * y.y + x.z * y.z;
}

//外積
vec4 cross(const vec4 v1, const vec4 v2)
{
    return vec4((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x));
}

vec4 faceforward(const vec4 N, const vec4 I, const vec4 R)
{
    float sw = 1.f - step(0.f, dot(R, I));
    return mix(-N, N, vec4(sw));
}

vec4 reflect(const vec4 I, const vec4 N)
{
    return I - 2.0 * dot(I, N) * N;
}

vec4 refract(const vec4 I, const vec4 N, const float eta)
{
    float ndoti = dot(N, I);
    float k = 1.f - eta * eta * (1.f - ndoti * ndoti);
    if (k < 0.f)
        return 0;
    else
        return eta * I - (eta * ndoti + sqrt(k)) * N;
}

vec4 lessThan(const vec4 x, const vec4 y)
{
    return vec4(1.f - step(y.x, x.x), 1.f - step(y.y, x.y), 1.f - step(y.z, x.z));
}

vec4 lessThanEqual(const vec4 x, const vec4 y)
{
    return vec4(step(x.x, y.x), step(x.y, y.y), step(x.z, y.z));
}

vec4 greaterThan(const vec4 x, const vec4 y)
{
    return vec4(1.f - step(x.x, y.x), 1.f - step(x.y, y.y), 1.f - step(x.z, y.z));
}

vec4 greaterThanEqual(const vec4 x, const vec4 y)
{
    return vec4(step(y.x, x.x), step(y.y, x.y), step(y.z, x.z));
}

vec4 equal(const vec4 x, const vec4 y)
{
    return vec4(x.x == y.x, x.y == y.y, x.z == y.z);
}

vec4 notEqual(const vec4 x, const vec4 y)
{
    return vec4(x.x != y.x, x.y != y.y, x.z != y.z);
}

float any(const vec4 x)
{
    return 1.f - (x.x == 0.f && x.y == 0.f && x.z == 0.f);
}

float all(const vec4 x)
{
    return x.x != 0.f && x.y != 0.f && x.z != 0.f;
}

vec4 _not(const vec4 x)
{
    return vec4(!x.x, !x.y, !x.z);
}

//////////////////////以下オリジナルの関数//////////////////////

//2次元の擬似乱数
//W.J.J. Rey, 22nd European Meeting of Statisticians and the 7th Vilnius Conference on Probability Theory and Mathematical Statistics, August 1998
vec4 random2(const vec4 x)
{
    vec4 d = vec4(dot(x, vec4(127.1, 311.7)), dot(x, vec4(269.5, 183.3)));
    vec4 f = sin(d) * 43758.5453123;
    return (f - floor(f)) * 2.f - 1.f;
}

//グラデーションノイズ生成
//Inigo Quilez - iq/2013 https://www.shadertoy.com/view/XdXGW8
float gradationNoise(const vec4 x)
{
    vec4 v = x;
    v.z = 0;
    v.w = 0;

    vec4 i = floor(v);
    vec4 f = v - i;

    vec4 v00 = random2(i);
    vec4 v10 = random2(i + vec4(1, 0));
    vec4 v01 = random2(i + vec4(0, 1));
    vec4 v11 = random2(i + vec4(1, 1));

    vec4 u = f * f * (f * -2.f + 3.f);

    float a = mix(dot(v00, f), dot(v10, f - vec4(1, 0)), u.x);
    float b = mix(dot(v01, f - vec4(0, 1)), dot(v11, f - vec4(1, 1)), u.x);
    return mix(a, b, u.y) + 0.5f;
}

//4行4列 x 4行1列の計算
vec4 mul4x4444(const vec4 l, const vec4 r[4])
{
    return vec4(r[0].x * l.x + r[1].x * l.y + r[2].x * l.z + r[3].x * l.w,
                r[0].y * l.x + r[1].y * l.y + r[2].y * l.z + r[3].y * l.w,
                r[0].z * l.x + r[1].z * l.y + r[2].z * l.z + r[3].z * l.w,
                r[0].w * l.x + r[1].w * l.y + r[2].w * l.z + r[3].w * l.w);
}

//UVを回転させる(angleは弧度法)
vec4 rotate(const vec4 uv, const float angle)
{
    vec4 v = uv;
    v.z = 0;
    v.w = 0;

    float angSin = sin(angle);
    float angCos = cos(angle);

    vec4 v4444[4] = {vec4(angCos, -angSin), vec4(angSin, angCos), 0, 0};

    return mul4x4444(v - 0.5f, v4444) + 0.5f;
}

vec4 vecRotateX(const vec4 vec, const float angle)
{
    float angSin = sin(angle);
    float angCos = cos(angle);

    vec4 v4444[4] = {vec4(1, 0, 0), vec4(0, angCos, -angSin), vec4(0, angSin, angCos), 0};

    return mul4x4444(vec, v4444);
}

vec4 vecRotateY(const vec4 vec, const float angle)
{
    float angSin = sin(angle);
    float angCos = cos(angle);

    vec4 v4444[4] = {vec4(angCos, 0, angSin), vec4(0, 1, 0), vec4(-angSin, 0, angCos), 0};

    return mul4x4444(vec, v4444);
}

vec4 vecRotateZ(const vec4 vec, const float angle)
{
    float angSin = sin(angle);
    float angCos = cos(angle);

    vec4 v4444[4] = {vec4(angCos, -angSin, 0), vec4(angSin, angCos, 0), vec4(0, 0, 1), 0};

    return mul4x4444(vec, v4444);
}

//ガウス関数
float gauss(const float a, const float x)
{
    return exp(-(x * x) / (2.f * a * a));
}

float lengthsqr(const vec4 x)
{
    return x.x * x.x + x.y * x.y + x.z * x.z;
}

float roundN(const float num, const int n)
{
    return round(num * pow(10, n - 1)) / pow(10, n - 1);
}

template float remap(const float v, const float inMin, const float inMax, const float outMin, const float outMax);
template vec4 remap(const vec4 v, const vec4 inMin, const vec4 inMax, const vec4 outMin, const vec4 outMax);
template <typename T>
T remap(const T v, const T inMin, const T inMax, const T outMin, const T outMax)
{
    return clamp(outMin + (v - inMin) * (outMax - outMin) / (inMax - inMin), outMin, outMax);
}

//スクリーン合成
vec4 screenSynthesis(const vec4 def, const vec4 syn)
{
    return def + syn - def * syn;
}

vec4 rainbow(const float v)
{
    return vec4((sin(v * 6.f) + 1.f) / 2.f,
                (sin((v + (1.f / 3.f)) * 6.f) + 1.f) / 2.f,
                (sin((v + (2.f / 3.f)) * 6.f) + 1.f) / 2.f);
}

//////////////////////以下vec4関係の関数//////////////////////

vec4::vec4()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

vec4::vec4(const float f)
{
    this->x = f;
    this->y = f;
    this->z = f;
    this->w = f;
}

vec4::vec4(const float x, const float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
    this->w = 0;
}

vec4::vec4(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
}

vec4::vec4(const float x, const float y, const float z, const float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

vec4 vec4::SetAll(const float f)
{
    this->x = f;
    this->y = f;
    this->z = f;
    this->w = f;
    return *this;
}

vec4 vec4::SetAll(const float x, const float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
    this->w = 0;
    return *this;
}

vec4 vec4::SetAll(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
    return *this;
}

vec4 vec4::SetAll(const float x, const float y, const float z, const float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}

vec4 operator+(const vec4 l, const vec4 r)
{
    return vec4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4 operator+(const float l, const vec4 r)
{
    return (vec4)l + r;
}

vec4 operator+(const vec4 l, const float r)
{
    return l + (vec4)r;
}

vec4 operator-(const vec4 l, const vec4 r)
{
    return vec4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4 operator-(const float l, const vec4 r)
{
    return (vec4)l - r;
}

vec4 operator-(const vec4 l, const float r)
{
    return l - (vec4)r;
}

vec4 operator*(const vec4 l, const vec4 r)
{
    return vec4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
}

vec4 operator*(const float l, const vec4 r)
{
    return (vec4)l * r;
}

vec4 operator*(const vec4 l, const float r)
{
    return l * (vec4)r;
}

vec4 operator/(const vec4 l, const vec4 r)
{
    return vec4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
}

vec4 operator/(const float l, const vec4 r)
{
    return (vec4)l / r;
}

vec4 operator/(const vec4 l, const float r)
{
    return l / (vec4)r;
}

vec4 operator-(const vec4 r)
{
    return -1.f * r;
}

void operator+=(vec4 &l, const vec4 r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
}

void operator+=(vec4 &l, const float r)
{
    l += (vec4)r;
}

void operator-=(vec4 &l, const vec4 r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
}

void operator-=(vec4 &l, const float r)
{
    l -= (vec4)r;
}

void operator*=(vec4 &l, const vec4 r)
{
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
}

void operator*=(vec4 &l, const float r)
{
    l *= (vec4)r;
}

void operator/=(vec4 &l, const vec4 r)
{
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
}

void operator/=(vec4 &l, const float r)
{
    l /= (vec4)r;
}

int operator==(const vec4 l, const vec4 r)
{
    return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}

int operator!=(const vec4 l, const vec4 r)
{
    return l.x != r.x || l.y != r.y || l.z != r.z || l.w != r.w;
}

std::ostream &operator<<(std::ostream &l, const vec4 &r)
{
    l << "(" << roundN(r.x, 3) << ", " << roundN(r.y, 3) << ", " << roundN(r.z, 3) << ", " << roundN(r.w, 3) << ")";
    return l;
}
