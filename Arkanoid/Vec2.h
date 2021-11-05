#pragma once
#include "SimpleMath.h"

using DirectX::SimpleMath::Vector2;

struct Vec2 : public Vector2
{
	Vec2();
	Vec2(float _x, float _y);
	Vec2(const Vec2& other);
	Vec2(const Vector2& Vec);

	bool operator== (const Vec2& target) const;
	bool operator!= (const Vec2& target) const;

	bool Equals(const Vec2& target, float epsilon = 0.01f) const;

	Vec2 rotateByAngle(const Vec2& pivot, float angle) const;
	Vec2 rotate(float angle) const;

	Vec2 Ortho() const;
	Vec2 OrthoR() const;
};

