#include "pch.h"
#include "Collision.h"
#include "Util.h"
#include <cassert>

void AABB::Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color)
{
	using DirectX::VertexPositionColor;

	VertexPositionColor v1(DirectX::SimpleMath::Vector3(m_min.x, m_max.y, 0.f), Color);
	VertexPositionColor v2(DirectX::SimpleMath::Vector3(m_max.x, m_max.y, 0.f), Color);
	VertexPositionColor v3(DirectX::SimpleMath::Vector3(m_min.x, m_min.y, 0.f), Color);
	VertexPositionColor v4(DirectX::SimpleMath::Vector3(m_max.x, m_min.y, 0.f), Color);
	
	Batch->DrawLine(v1, v2);
	Batch->DrawLine(v2, v4);
	Batch->DrawLine(v3, v4);
	Batch->DrawLine(v1, v3);
}
void AABB::Transform(AABB& ShapeToUpdate, const Transform2D& transform)
{
	ShapeToUpdate.m_min = transform.Apply(m_min);
	ShapeToUpdate.m_max = transform.Apply(m_max);
}

bool inside(const AABB& b0, const Vec2& p1)
{
	return b0.m_min.x <= p1.x && p1.x <= b0.m_max.x &&
		b0.m_min.y <= p1.y && p1.y <= b0.m_max.y;
}

bool intersect(const AABB& b0, const AABB& b1)
{
	return !(b0.m_min.x > b1.m_max.x || b0.m_max.x < b1.m_min.x ||
			b0.m_min.y > b1.m_max.y || b0.m_max.y < b1.m_min.y);
}

bool intersect(const AABB& b0, const Circle& c1)
{
	Vec2 closestPointOfCircleInBox(
		MathUtil::clamp(b0.m_min.x, b0.m_max.x, c1.m_center.x),
		MathUtil::clamp(b0.m_min.y, b0.m_max.y, c1.m_center.y)
	);

	return (closestPointOfCircleInBox - c1.m_center).LengthSquared() <= MathUtil::sqr(c1.m_radius);
}

bool intersect(const Circle& c0, const Circle& c1)
{
	return (c1.m_center - c0.m_center).LengthSquared() <= MathUtil::sqr(c0.m_radius + c1.m_radius);
}

bool intersect(const Line& l0, const Line& l1)
{
	Vec2 v0 = l0.m_p1 - l0.m_p0; //line 0
	Vec2 v1 = l1.m_p1 - l1.m_p0; //line 1
	Vec2 v1n = v1.Ortho();
	
	float denom = v0.Dot(v1n); //check orthogonality between line 0 and line 1 ortho
	if (MathUtil::equalWithEpsilon(denom, 0.0f, MathUtil::EPS))
	{
		// Parallel lines
		float t0 = v0.Dot(l1.m_p0 - l0.m_p0) / v0.Dot(v0);
		Vec2 closest = l0.m_p0 + v0 * t0;
		if (closest != l1.m_p0)
			return false;
		float t1 = v0.Dot(l1.m_p1 - l0.m_p0) / v0.Dot(v0);
		if (t0 > t1)
			std::swap(t0, t1);
		return !(t1 < 0.0f || t0 > 1.0f);
	}
	//perpendicular lines
	float t0 = (l1.m_p0 - l0.m_p0).Dot(v1n) / denom;
	if (t0 < 0.0f || t0 > 1.0f)
		return false;
	Vec2 v0n = v0.Ortho();
	float t1 = (l0.m_p0 - l1.m_p0).Dot(v0n) / v1.Dot(v0n);
	return 0.0f <= t1 && t1 <= 1.0f;
}

bool intersect(const Circle& c0, const Line& l1)
{
	Vec2 l = l1.m_p1 - l1.m_p0;
	float t = l.Dot(c0.m_center - l1.m_p0) / l.Dot(l); //get the value of ortho projecting c0.m_center - l1.m_p0 onto the line
	t = MathUtil::clamp(0.0f, 1.0f, t);
	Vec2 ClosestPointOnLine = l1.m_p0 + l * t; //get the point on line corresponding to the projection on line

	return (ClosestPointOnLine - c0.m_center).LengthSquared() <= MathUtil::sqr(c0.m_radius);
}

bool intersect(const AABB& b0, const Line& l1)
{
	if(inside(b0, l1.m_p0) || inside(b0, l1.m_p1))
		return true;

	Line diag;
	if (l1.m_p0.x < l1.m_p1.x && l1.m_p0.y < l1.m_p1.y || l1.m_p0.x >= l1.m_p1.x && l1.m_p0.y >= l1.m_p1.y)
	{
		diag.m_p0 = Vec2(b0.m_max.x, b0.m_min.y);
		diag.m_p1 = Vec2(b0.m_min.x, b0.m_max.y);
	}
	else
	{
		diag.m_p0 = b0.m_min;
		diag.m_p1 = b0.m_max;
	}
	return intersect(diag, l1);
}

void Line::Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color)
{
	DirectX::VertexPositionColor p0(DirectX::SimpleMath::Vector3(m_p0.x, m_p0.y, 0.f), Color);
	DirectX::VertexPositionColor p1(DirectX::SimpleMath::Vector3(m_p1.x , m_p1.y, 0.f), Color);
	Batch->DrawLine(p0, p1);
}

void Line::Transform(Line& ShapeToUpdate, const Transform2D& transform)
{
	ShapeToUpdate.m_p0 = transform.Apply(m_p0);
	ShapeToUpdate.m_p1 = transform.Apply(m_p1);
}

void Circle::Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* Batch, DirectX::XMVECTORF32 Color)
{
	static constexpr int CircleVertexCount = 128;
	DirectX::VertexPositionColor lines[CircleVertexCount];
	for (int i = 0; i < CircleVertexCount; ++i)
	{
			float t = DirectX::XM_PI * 2 * float(i) / 100;
			lines[i] = DirectX::VertexPositionColor(DirectX::SimpleMath::Vector3(m_radius * cos(t) + m_center.x, m_center.y + m_radius * -sin(t), 0.f), Color);
	}
	Batch->Draw(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, lines, CircleVertexCount);
}

void Circle::Transform(Circle& ShapeToUpdate, const Transform2D& transform)
{
	const Vec2 scale = transform.GetScale();
	float maxScale = std::max(scale.x, scale.y);
	ShapeToUpdate.m_radius = m_radius * maxScale;
	ShapeToUpdate.m_center = transform.Apply(m_center);
}
