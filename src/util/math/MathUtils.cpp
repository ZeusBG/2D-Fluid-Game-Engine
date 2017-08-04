#include "util/math/MathUtils.h"
#include "util/math/Vec.h"
#include "util/math/Mat.h"


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

float MathUtils::Dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + 
           v1.y * v2.y + 
           v1.z + v2.z;
}


Mat3x3 MathUtils::Multiply3x3Mat(const Mat3x3& left, const Mat3x3& right)
{
    Mat3x3 rightTransposed = MathUtils::Transpose(right);
    Mat3x3 result;

    result[0][0] = MathUtils::Dot(left.GetRowI() , rightTransposed.GetRowI());
    result[1][0] = MathUtils::Dot(left.GetRowJ() , rightTransposed.GetRowI());
    result[2][0] = MathUtils::Dot(left.GetRowK() , rightTransposed.GetRowI());

    return result;
}
