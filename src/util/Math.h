#pragma once

#include <math.h>
#include <DirectXMath.h>

struct Vec2
{
    float x, y;

    Vec2(float x, float y) : x(x), y(y)
    {}

    void Normalize()
    {
        float length = sqrt(x *x + y * y);
        x /= length;
        y /= length;
    }
};

struct Mat2x2
{
    float mat[2][2];
    static Mat2x2 Identity()
    {
        Mat2x2 identity;
        identity[0][0] = 1.0f;
        identity[0][1] = 0.0f;
        identity[1][0] = 0.0f;
        identity[1][1] = 1.0f;
    }

    float* operator[](int idx) { return mat[idx]; }
};

struct Vec3
{
    float x, y, z;

    Vec3(float x, float y, float z) : x(x), y(y), z(z)
    {}

    void Normalize()
    {
        float length = sqrt(x *x + y * y + z * z);
        x /= length;
        y /= length;
        z /= length;
    }

};
struct Mat3x3
{
public:
    Mat3x3() { SetIdentity(); }

    //TODO istoilov : Figure a way to save the 2nd create;
    inline Vec3 GetRowI() const { return Vec3(mat[0][0], mat[0][1], mat[0][2]); }
    inline Vec3 GetRowJ() const { return Vec3(mat[1][0], mat[1][1], mat[1][2]); }
    inline Vec3 GetRowK() const { return Vec3(mat[2][0], mat[2][1], mat[2][2]); }

    void SetIdentity();

    DirectX::XMMATRIX ToXMMATRIX() const;

    float mat[3][3];
};


class MathUtils
{
public:
    static Mat3x3 Transpose(const Mat3x3& mat);
};
float dotProduct(const Vec2& v1, const Vec2& v2);
