#include "util/math/Vec.h"
#include "util/math/MathUtils.h"

#include <math.h>

Vec2 Vec2::Zero = Vec2();
Vec2 Vec2::BaseI = Vec2(1.f, 0.f);
Vec2 Vec2::BaseJ = Vec2(0.f, 1.f);

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

// ==================================
// ====== Vec3 Implementation =======
// ==================================

Vec3 Vec3::Zero  = Vec3(0.f, 0.f, 0.f);
Vec3 Vec3::BaseI = Vec3(1.f, 0.f, 0.f);
Vec3 Vec3::BaseJ = Vec3(0.f, 1.f, 0.f);
Vec3 Vec3::BaseK = Vec3(0.f, 0.f, 1.f);

void Vec3::Normalize()
{
    float length = sqrtf(x *x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}