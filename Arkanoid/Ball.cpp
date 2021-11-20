#include "pch.h"
#include "Ball.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "InputHandler.h"
#include "Util.h"
#include <iostream>

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

	SetSpeed(250.f);
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

			for (BaseObject* collision : collisions)
			{
				CollisionComponent* collissionCc = collision->GetComponent<CollisionComponent>();
				if (collissionCc)
				{
					Vec2 CurrentVelocity = ReflectedVelocity.Equals(Vec2::Zero) ? GetVelocity() : ReflectedVelocity;

					Vec2 CollisionNormal = m_collisionComp->GetCollisionNormalWithObject(collision, CurrentVelocity);
					CollisionNormal.Normalize();

					const float ReflectionQuantity = CurrentVelocity.Dot(CollisionNormal);
					
					ReflectedVelocity += CurrentVelocity - 2.f * (ReflectionQuantity * CollisionNormal); //law of reflection			

					if (MovableObject* Movable = dynamic_cast<MovableObject*>(collision))
					{
						ReflectedVelocity += 0.45f * Movable->GetVelocity();
					}

					std::string out = "Velocity X" + std::to_string(ReflectedVelocity.x) + "Y " + std::to_string(ReflectedVelocity.y);
					OutputDebugStringA(out.c_str());
					SetVelocity(ReflectedVelocity);
				}
			}
		}
	}
}

