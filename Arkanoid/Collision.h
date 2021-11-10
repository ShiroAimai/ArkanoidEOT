#pragma once
#include "Vec2.h"
#include "Transform2D.h"

struct AABB
{
	Vec2 m_min, m_max;

	AABB() = default;
	AABB(const Vec2& min, const Vec2& max) : m_min(min), m_max(max) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch);
	void Transform(AABB& ShapeToUpdate, const Transform2D& transform);
};

struct Circle
{
	Vec2 m_center;
	float m_radius;

	Circle() = default;
	Circle(const Vec2& center, float radius) : m_center(center), m_radius(radius) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch) {};
	void Transform(Circle& ShapeToUpdate, const Transform2D& transform);
};

struct Line
{
	Vec2 m_p0, m_p1;

	Line() = default;
	Line(const Vec2& p0, const Vec2& p1) : m_p0(p0), m_p1(p1) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch);
	void Transform(Line& ShapeToUpdate, const Transform2D& transform);
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
	virtual bool intersect(const Line& l1) const = 0;
	virtual bool intersect(const BaseShape& other) const = 0;

	virtual void Transform(const Transform2D& transform) = 0;

	virtual void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch) = 0;
};

template <class S>
class Shape : public BaseShape {
private:
	S m_updatedShape;

public:
	S m_originalShape;

	virtual void Transform(const Transform2D& transform) override
	{
		m_originalShape.Transform(m_updatedShape, transform);
	}

	virtual bool intersect(const AABB& b1) const override
	{
		return ::intersect(m_updatedShape, b1);
	}

	virtual bool intersect(const Circle& c1) const override
	{
		return ::intersect(m_updatedShape, c1);
	}

	virtual bool intersect(const Line& l1) const override
	{
		return ::intersect(m_updatedShape, l1);
	}

	virtual bool intersect(const BaseShape& other) const
	{
		return other.intersect(m_updatedShape);
	}

	virtual void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch) override
	{
		m_updatedShape.Draw(Batch);
	}

};
