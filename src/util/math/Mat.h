#pragma once
#include "util/math/Vec.h"
#include <DirectXMath.h>

class Mat2x2
{
public:
    Mat2x2()
    {}

    Mat2x2(float x00, float x01, float x10, float x11)
    {
        mat[0][0] = x00;
        mat[0][1] = x01;
        mat[1][0] = x10;
        mat[1][1] = x11;
    }

    static Mat2x2 Identity()
    {
        Mat2x2 identity;
        identity[0][0] = 1.0f;
        identity[0][1] = 0.0f;
        identity[1][0] = 0.0f;
        identity[1][1] = 1.0f;
    }

    DirectX::XMMATRIX ToXMMATRIX() const;
    float* operator[](int idx) { return mat[idx]; }

    Vec2 operator* (const Vec2& other)
    {
        Vec2 result;
        result.x = mat[0][0] * other.x + mat[0][1] * other.y;
        result.y = mat[1][0] * other.x + mat[1][1] * other.y;
    }
public:
    float mat[2][2];
};

class Mat3x3
{
public:
    //TODO istoilov : Figure a way to save the 2nd create;
    inline Vec3 GetRowI() const { return Vec3(mat[0][0], mat[0][1], mat[0][2]); }
    
    inline Vec3 GetRowJ() const { return Vec3(mat[1][0], mat[1][1], mat[1][2]); }
    inline Vec2 GetRowJ2() const { return Vec2(mat[1][0], mat[1][1]); }

    inline Vec3 GetRowK() const { return Vec3(mat[2][0], mat[2][1], mat[2][2]); }

    inline void SetRowI(const Vec2& v) { mat[0][0] = v.x, mat[0][1] = v.y; }
    inline void SetRowJ(const Vec2& v) { mat[1][0] = v.x, mat[1][1] = v.y; }
    inline void SetRowK(const Vec2& v) { mat[2][0] = v.x, mat[2][1] = v.y; }


    void operator*= (const Mat3x3& right);
    float* operator[](int idx) { return mat[idx]; }

    static Mat3x3 GetRotateMatrix(const float rad)
    {
        Mat3x3 result;
        result[0][0] = cosf(rad); result[0][1] = -sinf(rad); result[0][2]= 0.f;
        result[1][0] = sinf(rad); result[1][1] =  cosf(rad); result[1][2]= 0.f;
        result[2][0] =      0.f; result[2][1] =       0.f; result[2][2]= 1.f;
        return result;
    }

    static Mat3x3 Identity()
    {
        Mat3x3 identity;
        identity[0][0] = 1.0f; identity[0][1] = 0.0f; identity[0][2] = 0.0f;
        identity[1][0] = 0.0f; identity[1][1] = 1.0f; identity[1][2] = 0.0f;
        identity[2][0] = 0.0f; identity[2][1] = 0.0f; identity[2][2] = 1.0f;
        return identity;
    }

    DirectX::XMMATRIX ToXMMATRIX() const;

    void Translate(float x, float y, float z)
    {
        mat[0][2] += x;
        mat[1][2] += y;
        //mat[2][2] += z;
    }

    

public:
    float mat[3][3];

};