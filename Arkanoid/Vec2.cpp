#include "pch.h"
#include "Vec2.h"

Vec2::Vec2() : Vector2(0.f, 0.f)
{

}

Vec2::Vec2(float _x, float _y) : Vector2(_x, _y)
{

}

Vec2::Vec2(const Vec2& other)
{
	x = other.x;
	y = other.y;
}

Vec2::Vec2(const Vector2& Vec) : Vec2(Vec.x, Vec.y)
{

}

bool Vec2::Equals(const Vec2& target, float epsilon /*= 0.01f*/) const
{
	//avoid usage of abs
	if (x - epsilon <= target.x && target.x <= x + epsilon)
		if (y - epsilon <= target.y && target.y <= y + epsilon)
			return true;
	return false;
}


Vec2 Vec2::rotateByAngle(const Vec2& pivot, float angle) const
{
	const Vec2 Diff = *this - pivot;
	return pivot + Diff.rotate(angle);
}

Vec2 Vec2::rotate(float angle) const
{
	float cos = cosf(angle);
	float sin = sinf(angle);
	return Vec2(x * cos - y * sin, x * sin + y * cos);
}

bool Vec2::operator!=(const Vec2& target) const
{
	return !(*this == target);
}

bool Vec2::operator==(const Vec2& target) const
{
	return Equals(target);
}