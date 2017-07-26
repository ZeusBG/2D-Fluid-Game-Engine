#include "util/Math.h"

float dotProduct(const Vec2& v1, const Vec2& v2)
{
    return v1.x * v2.x + v1.y + v2.y;
}

void Mat3x3::SetIdentity()
{
    mat[0][0] = 1; mat[0][1] = 0;  mat[0][2] = 0;
    mat[1][0] = 0; mat[1][1] = 1;  mat[1][2] = 0;
    mat[2][0] = 0; mat[2][1] = 0;  mat[2][2] = 1;
}

DirectX::XMMATRIX Mat3x3::ToXMMATRIX() const 
{
    DirectX::XMMATRIX result;

    result.r[0] = DirectX::XMVectorSet(mat[0][0], mat[0][1], mat[0][2], 0);
    result.r[0] = DirectX::XMVectorSet(mat[1][0], mat[1][1], mat[1][2], 0);
    result.r[0] = DirectX::XMVectorSet(mat[2][0], mat[2][1], mat[2][2], 0);
    result.r[0] = DirectX::XMVectorSet(        0,         0,         0, 1);

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