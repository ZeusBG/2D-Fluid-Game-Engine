#include "util/math/Vec.h"
#include "util/math/MathUtils.h"

#include <math.h>

Vec2 Vec2::Zero = Vec2();

void Vec2::Normalize()
{
    float length = sqrtf(x *x + y * y);
    x /= length;
    y /= length;
}

Vec2 Vec2::GetNormalized()
{
    Vec2 result = *this;
    result.Normalize();
    return result;
}

bool Vec2::EqualWithEpsilon(const Vec2& rhs) const
{
    if (x - EPSILON <= rhs.x && rhs.x <= x + EPSILON)
        if (y - EPSILON <= rhs.y && rhs.y <= y + EPSILON)
            return true;
    return false;


}
Vec2::Vec2(const Vec2& other) : x(other.x), y(other.y)
{}
Vec2::Vec2(float x, float y) : x(x), y(y)
{}
Vec2::Vec2() : x(0.f), y(0.f)
{}


void Vec3::Normalize()
{
    float length = sqrtf(x *x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}