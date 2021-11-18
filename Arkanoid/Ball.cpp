#include "pch.h"
#include "Ball.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "InputHandler.h"

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

	SetSpeed(240.f);
	SetVelocity(Vec2(0.f, 0.f));
}

void Ball::FixedUpdate()
{
	MovableObject::FixedUpdate();

	if (m_collisionComp)
	{
		std::vector<BaseObject*> collisions = m_collisionComp->GetCollisions();

		if (collisions.size() > 0)
		{
			BaseObject* FirstCollisionObject = collisions[0];
			CollisionComponent* FirstCollisionObjectCc = FirstCollisionObject->GetComponent<CollisionComponent>();
			if (FirstCollisionObjectCc)
			{
				Vec2 CurrentVelocity = GetVelocity();

				Vec2 CollisionNormal = m_collisionComp->GetCollisionNormalWithObject(FirstCollisionObject, CurrentVelocity);
				CollisionNormal.Normalize();

				Vec2 ReflectedVelocity = CurrentVelocity - 2.f * (CurrentVelocity.Dot(CollisionNormal) * CollisionNormal); //law of reflection
				
				SetVelocity(ReflectedVelocity);
			}
		}

	}
}


