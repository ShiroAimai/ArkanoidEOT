#include "pch.h"
#include "Ball.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "InputHandler.h"
#include "Util.h"
#include <iostream>
#include "Brick.h"

namespace {
	float CollidedMovableVelocityMultiplier = 0.45f;
}

Ball::Ball(float radius) : m_radius(radius)
{
	Shape<Circle>* circle = new Shape<Circle>;
	circle->m_originalShape.m_center = Vec2(0, 0);
	circle->m_originalShape.m_radius = m_radius;
	m_collisionComp = new CollisionComponent(circle);
	m_collisionComp->SetShapeColor(DirectX::Colors::OrangeRed);
	AddComponent(m_collisionComp);

	Sprite* sprite = Sprite::Load(L"Assets/ball.png");
	m_visualComp = new VisualComponent(sprite);
	AddComponent(m_visualComp);

	SetSpeed(300.f);
	SetVelocity(Vec2::Zero);
}


void Ball::FixedUpdate()
{
	// evaluate collisions
 	MovableObject::FixedUpdate();

	if (m_collisionComp)
	{
		std::vector<BaseObject*> collisions = m_collisionComp->GetCollisions();

		if (collisions.size() > 0)
		{
			Vec2 ReflectedVelocity = Vec2::Zero;

			BaseObject* Other = collisions[0];
			CollisionComponent* collissionCc = Other->GetComponent<CollisionComponent>();
			if (collissionCc)
			{
				Vec2 CurrentVelocity = GetVelocity();
				Vec2 CollisionNormal = m_collisionComp->GetCollisionNormalWithObject(Other, CurrentVelocity);
				CollisionNormal.Normalize();

				const float ReflectionAngle = CurrentVelocity.Dot(CollisionNormal);

				ReflectedVelocity = CurrentVelocity - 2.f * (ReflectionAngle * CollisionNormal); //law of reflection			

				if (MovableObject* Movable = dynamic_cast<MovableObject*>(Other))
				{
					ReflectedVelocity += CollidedMovableVelocityMultiplier * Movable->GetVelocity();
				}

				SetVelocity(ReflectedVelocity);
			}

		}
	}
}

bool Ball::IsBlocker(BaseObject* Object) const
{
	return dynamic_cast<Brick*>(Object) || MovableObject::IsBlocker(Object);
}

