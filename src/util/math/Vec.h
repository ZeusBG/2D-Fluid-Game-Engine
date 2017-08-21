#pragma once
#include <math.h>

class Vec2
{
public:
    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2& other);

    void Normalize();
    Vec2 GetNormalized();

    void operator= (const Vec2& rhs) { x = rhs.x; y = rhs.y; }

    bool operator!= (const Vec2& rhs) const { return (x != rhs.x || y != rhs.y); }

    Vec2 operator* (const float c) const { return Vec2(x*c, y * c); }
    Vec2 operator- (const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator+ (const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

    bool EqualWithEpsilon(const Vec2& rhs) const;

    inline float GetLength() const
    {
        return sqrtf(x*x + y*y);
    }

    inline float GetLengthSq() const
    {
        return Dot(*this);
    }

    inline float Dot(const Vec2& other) const { return x*other.x + y*other.y; }
    inline Vec2 GetPerp() const { return Vec2(-y, x); }
    inline Vec2 getRPerp() const { return Vec2(y, -x); }

    Vec2 rotateByAngle(const Vec2& pivot, float angle) const;

    inline Vec2 Rotate(float angle) const
    {
        float cos = cosf(angle);
        float sin = sinf(angle);
        return Vec2(x*cos - y*sin, x*sin + y*cos);
    }

    static Vec2 Zero;
    static Vec2 BaseI;
    static Vec2 BaseJ;
public:
    float x;
    float y;
};


class Vec3
{
public:
    Vec3() : x(0), y(0), z(0)
    {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z)
    {}

    void Normalize();

    void operator= (const Vec3& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; }
    void operator= (const Vec2& rhs) { x = rhs.x; y = rhs.y; }

    float GetLength() const { return sqrtf(Dot(*this)); }
    float GetLengthSqr() const { return Dot(*this); }

    float Dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

    bool operator!= (const Vec3& rhs) const { return (x != rhs.x || y != rhs.y || z != rhs.z); }

    Vec3 operator* (const float c)   const { return Vec3(x*c, y * c, z*c); }
    Vec3 operator- (const Vec3& rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vec3 operator+ (const Vec3& rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    void operator+= (const Vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }

    bool operator< (const Vec3& rhs) { return GetLengthSqr() < rhs.GetLengthSqr(); }
    bool operator> (const Vec3& rhs) { return GetLengthSqr() > rhs.GetLengthSqr(); }

    static Vec3 Zero;
    static Vec3 BaseI;
    static Vec3 BaseJ;
    static Vec3 BaseK;

public:
    float x;
    float y;
    float z;
};