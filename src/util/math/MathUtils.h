#pragma once
#define EPSILON 0.001
#define PI 3.141592
#define PI_2 1.570796

class Mat2x2;
class Mat3x3;
class Vec2;
class Vec3;
class MathUtils
{
public:
    static Mat3x3 Multiply3x3Mat(const Mat3x3& left, const Mat3x3& right);
    static Mat3x3 Transpose(const Mat3x3& mat);
    static float Dot(const Vec2& v1, const Vec2& v2);
    static float Dot(const Vec3& v1, const Vec3& v2);
};
