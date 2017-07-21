#pragma once
#include <math.h>
struct Vec2
{
	float x, y;

	Vec2(float x, float y): x(x), y(y)
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

struct Mat3x3
{
	float mat[3][3];
};

float dot(const Vec2& v1, const Vec2& v2)
{
	return v1.x * v2.x + v1.y + v2.y;
}
