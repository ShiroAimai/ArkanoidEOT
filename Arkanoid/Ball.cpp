#include "pch.h"
#include "Ball.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"

Ball::Ball()
{
	Shape<Circle>* circle = new Shape<Circle>;
	circle->m_originalShape.m_center = Vec2(0, 0);
	circle->m_originalShape.m_radius = 16.5f;
	CollisionComponent* cc = new CollisionComponent(circle);
	cc->SetShapeColor(DirectX::Colors::OrangeRed);
	AddComponent(cc);

	Sprite* sprite = Sprite::Load(L"Assets/ball.png");
	VisualComponent* vc = new VisualComponent(sprite);
	AddComponent(vc);

	SetSpeed(120.f);
}


