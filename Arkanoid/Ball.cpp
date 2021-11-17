#include "pch.h"
#include "Ball.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "InputHandler.h"

Ball::Ball()
{
	Shape<Circle>* circle = new Shape<Circle>;
	circle->m_originalShape.m_center = Vec2(0, 0);
	circle->m_originalShape.m_radius = 16.5f;
	mCollisionComponent = new CollisionComponent(circle);
	mCollisionComponent->SetShapeColor(DirectX::Colors::OrangeRed);
	AddComponent(mCollisionComponent);

	Sprite* sprite = Sprite::Load(L"Assets/ball.png");
	VisualComponent* vc = new VisualComponent(sprite);
	AddComponent(vc);

	SetSpeed(240.f);

	SetVelocity(Vec2(0.5f, 0.5f));
}

void Ball::FixedUpdate()
{
	MovableObject::FixedUpdate();
	
	if (mCollisionComponent)
	{
		std::vector<BaseObject*> collisions = mCollisionComponent->GetCollisions();

		if (collisions.size() > 0)
		{
			BaseObject* FirstCollisionObject = collisions[0];
			CollisionComponent* FirstCollisionObjectCc = FirstCollisionObject->GetComponent<CollisionComponent>();
			if (FirstCollisionObjectCc)
			{
				Vec2 CurrentVelocity = GetVelocity();
				CurrentVelocity.Normalize();

				FirstCollisionObjectCc->FixedUpdate(); //make sure collision are updated without waiting for update call
				Vec2 CollisionNormal = mCollisionComponent->GetCollisionNormalWithObject(FirstCollisionObject, CurrentVelocity);
				CollisionNormal.Normalize();

				Vec2 ReflectedVelocity = CurrentVelocity - 2.f * (CurrentVelocity.Dot(CollisionNormal) * CollisionNormal); //law of reflection

				MovableObject* FirstCollisionObjectAsMovable = dynamic_cast<MovableObject*>(FirstCollisionObject);
				if (FirstCollisionObjectAsMovable)
				{
					ReflectedVelocity += FirstCollisionObjectAsMovable->GetVelocity();
				}

				SetVelocity(ReflectedVelocity);
			}
		}
	}
}


