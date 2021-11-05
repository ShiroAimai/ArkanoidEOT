#pragma once
#include "Vec2.h"

struct AABB
{
	Vec2 m_min, m_max;

	AABB() = default;
	AABB(const Vec2& min, const Vec2& max) : m_min(min), m_max(max) {}

	void Draw() {};
};

struct Circle
{
	Vec2 m_center;
	float m_radius;

	Circle() = default;
	Circle(const Vec2& center, float radius) : m_center(center), m_radius(radius) {}

	void Draw() {};
};

struct Line
{
	Vec2 m_p0, m_p1;

	Line() = default;
	Line(const Vec2& p0, const Vec2& p1) : m_p0(p0), m_p1(p1) {}

	void Draw() {};
};

bool inside(const AABB& b0, const Vec2& p1);

bool intersect(const AABB& b0, const AABB& b1);
bool intersect(const AABB& b0, const Circle& c1);
bool intersect(const AABB& b0, const Line& l1);

bool intersect(const Circle& c0, const Line& l1);
bool intersect(const Circle& c0, const Circle& c1);

bool intersect(const Line& l0, const Line& l1);

inline bool intersect(const Circle& c0, const AABB& b1) { return intersect(b1, c0); }
inline bool intersect(const Line& l0, const Circle& c1) { return intersect(c1, l0); }
inline bool intersect(const Line& l0, const AABB& b1) { return intersect(b1, l0); }

class BaseShape {
public:
	virtual ~BaseShape() {};
	virtual bool intersect(const AABB& b1) const = 0;
	virtual bool intersect(const Circle& c1) const = 0;
	virtual bool intersect(const BaseShape& other) const = 0;

	virtual void Draw() = 0;
};

template <class S>
class Shape : public BaseShape {
public:
	S m_Shape;

	virtual bool intersect(const AABB& b1) const override
	{
		return ::intersect(m_Shape, b1);
	}

	virtual bool intersect(const Circle& c1) const override
	{
		return ::intersect(m_Shape, c1);
	}

	virtual bool intersect(const BaseShape& other) const
	{
		return other.intersect(m_Shape);
	}

	virtual void Draw() override
	{
		m_Shape.Draw();
	}

};
