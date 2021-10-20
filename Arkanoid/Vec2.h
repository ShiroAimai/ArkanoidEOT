#pragma once
#include "SimpleMath.h"

struct Vec2 : public DirectX::SimpleMath::Vector2
{
	Vec2();
	Vec2(float _x, float _y);
	Vec2(const Vec2& other);

	Vec2& operator= (const Vec2& other);
	Vec2& operator+=(const Vec2& right);
	Vec2& operator-=(const Vec2& right);
	Vec2& operator*=(float scalar);
	Vec2& operator/=(float scalar);

	Vec2 operator-() const;

	bool operator== (const Vec2& target) const;
	bool operator!= (const Vec2& target) const;

	bool Equals(const Vec2& target, float epsilon = 0.01f) const;

	Vec2 normalize() const;

	float length() const;
	float sqrLength() const;

	Vec2 rotateByAngle(const Vec2& pivot, float angle) const;
	Vec2 rotate(float angle) const;
};

inline Vec2 operator+(const Vec2& left, const Vec2& right)
{
	Vec2 res(left);
	res += right;
	return res;
}

inline Vec2 operator-(const Vec2& left, const Vec2& right)
{
	Vec2 res(left);
	res -= right;
	return res;
}

inline Vec2 operator*(const Vec2& vec, float scalar)
{
	Vec2 res(vec);
	res*= scalar;
	return vec;
}

inline Vec2 operator/(const Vec2& vec, float scalar)
{
	Vec2 res(vec);
	res /= scalar;
	return vec;
}

inline float Dot(const Vec2& first, const Vec2& second)
{
	return first.x * second.x + first.y * second.y;
}

inline Vec2 Ortho(const Vec2& vec)
{
	return Vec2(-vec.y, vec.x);
}

inline Vec2 OrthoR(const Vec2& vec)
{
	return Vec2(vec.y, -vec.x);
}