#pragma once
#include "Vec2.h"
#include "Transform2D.h"

struct AABB
{
	Vec2 m_min, m_max;

	AABB() = default;
	AABB(const Vec2& min, const Vec2& max) : m_min(min), m_max(max) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color);
	void Transform(AABB& ShapeToUpdate, const Transform2D& transform);
	
	template<class T>
	Vec2 GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const;
};

template<class T>
inline Vec2 AABB::GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const
{
	Line top(m_min, Vec2(m_max.x, m_min.y));
	Line left(Vec2(m_min.x, m_max.y), m_min);
	Line right(m_max, Vec2(m_max.x, m_min.y));
	Line bottom(Vec2(m_min.x, m_max.y), m_max);

	std::vector<Vec2> Normals;

	if (::intersect(OtherShape, top))
	{
		Normals.push_back(-Vec2::UnitY);
	}
	
	if (::intersect(OtherShape, bottom))
	{
		Normals.push_back(Vec2::UnitY);
	}

	if (::intersect(OtherShape, left))
	{
		Normals.push_back(-Vec2::UnitX);
	}

	if (::intersect(OtherShape, right))
	{
		Normals.push_back(Vec2::UnitX);
	}

	Vec2 SelectedNormal = Vec2::Zero;
	float BestMatch = 1.f; 
	Vec2 VelDirection = Velocity;
	VelDirection.Normalize();
	for (Vec2 Normal : Normals)
	{
		float cos = VelDirection.Dot(Normal);
		if (cos < BestMatch)
		{
			BestMatch = cos;
			SelectedNormal = Normal;
		}
	}

	return SelectedNormal;
}

struct Circle
{
	Vec2 m_center;
	float m_radius;

	Circle() = default;
	Circle(const Vec2& center, float radius) : m_center(center), m_radius(radius) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color);
	void Transform(Circle& ShapeToUpdate, const Transform2D& transform);
	
	template<class T>
	Vec2 GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const;
};

template<class T>
inline Vec2 Circle::GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const
{
	return Vec2(-Velocity.x, -Velocity.y);
}

struct Line
{
	Vec2 m_p0, m_p1;

	Line() = default;
	Line(const Vec2& p0, const Vec2& p1) : m_p0(p0), m_p1(p1) {}

	void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color);
	void Transform(Line& ShapeToUpdate, const Transform2D& transform);
	
	template<class T>
	Vec2 GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const;
};

template<class T>
inline Vec2 Line::GetCollisionNormal(const T& OtherShape, const Vec2& Velocity) const
{
	Vec2 line = m_p1 - m_p0;
	line.Normalize();

	const Vec2 n1 = line.Ortho();
	if (Velocity.Dot(n1) < 0.f) return n1;
	const Vec2 n2 = line.OrthoR();
	if (Velocity.Dot(n2) < 0.f) return n2;

	return Vec2::Zero;
}

bool inside(const AABB& b, const Vec2& p);
bool inside(const Circle& c, const Vec2& p);
bool inside(const Line& l, const Vec2& p);


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

	virtual Vec2 GetCollisionNormal(const AABB& OtherShape, const Vec2& Velocity) const = 0;
	virtual Vec2 GetCollisionNormal(const Circle& OtherShape, const Vec2& Velocity) const = 0;
	virtual Vec2 GetCollisionNormal(const Line& OtherShape, const Vec2& Velocity) const = 0;
	virtual Vec2 GetCollisionNormal(const BaseShape& OtherShape, const Vec2& Velocity) const = 0;

	virtual bool Inside(const Vec2& p) const = 0;

	virtual void Transform(const Transform2D& transform) = 0;

	virtual void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color) = 0;
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

	virtual bool Inside(const Vec2& p) const override
	{
		return ::inside(m_updatedShape, p);
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

	virtual void Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color) override
	{
		m_updatedShape.Draw(Batch, Color);
	}

	virtual Vec2 GetCollisionNormal(const AABB& OtherShape, const Vec2& Velocity) const override
	{
		return m_updatedShape.GetCollisionNormal<AABB>(OtherShape, Velocity);
	}

	virtual Vec2 GetCollisionNormal(const Circle& OtherShape, const Vec2& Velocity) const override
	{
		return m_updatedShape.GetCollisionNormal<Circle>(OtherShape, Velocity);
	}
	
	virtual Vec2 GetCollisionNormal(const Line& OtherShape, const Vec2& Velocity) const override
	{
		return m_updatedShape.GetCollisionNormal<Line>(OtherShape, Velocity);
	}

	virtual Vec2 GetCollisionNormal(const BaseShape& OtherShape, const Vec2& Velocity) const override
	{
		if(!intersect(OtherShape)) return Vec2::Zero;
		
		return OtherShape.GetCollisionNormal(m_updatedShape, Velocity);
	}
};
