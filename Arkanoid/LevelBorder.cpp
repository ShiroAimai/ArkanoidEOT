#include "pch.h"
#include "LevelBorder.h"
#include "CollisionComponent.h"
#include "Collision.h"

LevelBorder::LevelBorder(const Vec2& p0, const Vec2& p1)
{
	Shape<Line>* shape = new Shape<Line>;
	shape->m_originalShape.m_p0 = p0;
	shape->m_originalShape.m_p1 = p1;
	CollisionComponent* cc = new CollisionComponent(shape);
	AddComponent(cc);
}