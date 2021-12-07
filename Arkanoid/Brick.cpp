#include "pch.h"
#include "Brick.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "VisualComponent.h"
#include "Sprite.h"

Brick::Brick(int width, int height) : m_width(width), m_height(height)
{ 
	float halfWidth = m_width / 2.f;
	float halfHeight = m_height / 2.f;
	Shape<AABB>* box = new Shape<AABB>();
	box->m_originalShape.m_min = Vec2(-halfWidth - 0.5f, -halfHeight);
	box->m_originalShape.m_max = Vec2(halfWidth + 0.5f, halfHeight);
	m_collisionComp = new CollisionComponent(box);
	m_collisionComp->SetShapeColor(DirectX::Colors::Violet);
	AddComponent(m_collisionComp);

	Sprite* sprite = Sprite::LoadStatic("brick", L"Assets/brick.png");
	m_visualComp = new VisualComponent(sprite);
	m_visualComp->SetColor(DirectX::Colors::Red);
	AddComponent(m_visualComp);
}