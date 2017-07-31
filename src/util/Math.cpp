#include "util/Math.h"

Vec2 Vec2::Zero = Vec2();

bool Vec2::EqualWithEpsilon(const Vec2& rhs) const
{
    if (x - EPSILON <= rhs.x && rhs.x <= x + EPSILON)
        if (y - EPSILON <= rhs.y && rhs.y <= y + EPSILON)
            return true;
    return false;

}
    
DirectX::XMMATRIX Mat2x2::ToXMMATRIX() const
{
    DirectX::XMMATRIX result;

    result.r[0] = DirectX::XMVectorSet(mat[0][0], mat[0][1], 0.f, 0);
    result.r[1] = DirectX::XMVectorSet(mat[1][0], mat[1][1], 0.f, 0);
    result.r[2] = DirectX::XMVectorSet(mat[2][0], mat[2][1], 0.f, 0);
    result.r[3] = DirectX::XMVectorSet(0, 0, 0, 1);

    return result;
}

DirectX::XMMATRIX Mat3x3::ToXMMATRIX() const 
{
    DirectX::XMMATRIX result;
    result.r[0] = DirectX::XMVectorSet(mat[0][0], mat[0][1], 0, mat[0][2]);
    result.r[1] = DirectX::XMVectorSet(mat[1][0], mat[1][1], 0, mat[1][2]);
    result.r[2] = DirectX::XMVectorSet(mat[2][0], mat[2][1], 1, mat[2][2]);
    result.r[3] = DirectX::XMVectorSet(        0,         0,         0, 1);

    return result;
}

Mat3x3 MathUtils::Transpose(const Mat3x3& mat)
{
    Mat3x3 result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result.mat[i][j] = mat.mat[j][i];
        }
    }
    return result;
}
float MathUtils::Dot(const Vec2& v1, const Vec2& v2)
{
    return v1.x * v2.x + v1.y + v2.y;
}

