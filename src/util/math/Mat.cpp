#include "util/math/Mat.h"
#include "util/math/MathUtils.h"

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
    result.r[2] = DirectX::XMVectorSet(mat[2][0], mat[2][1], 1, 0);
    result.r[3] = DirectX::XMVectorSet(0, 0, 0, 1);

    return result;

}
void Mat3x3::operator*= (const Mat3x3& right)
{
    *this = MathUtils::Multiply3x3Mat(*this, right);
}