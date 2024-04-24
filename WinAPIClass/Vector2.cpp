#include "Vector2.h"

tagVector2 tagVector2::operator+(const tagVector2& v)
{
	return { x + v.x, y + v.x };
}

tagVector2 tagVector2::operator-(const tagVector2& v)
{
	return { x - v.x, y - v.y };
}

tagVector2 tagVector2::operator*(const float f)
{
	return { x * f,y * f };
}

tagVector2& tagVector2::operator+=(const tagVector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

tagVector2& tagVector2::operator-=(const tagVector2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

tagVector2& tagVector2::operator*=(const float f)
{
	x *= f;
	y *= f;

	return *this;
}

tagVector2::tagVector2()
	: x(0.0f), y(0.0f)
{
}

tagVector2::tagVector2(float x, float y)
	: x(x), y(y)
{
}
