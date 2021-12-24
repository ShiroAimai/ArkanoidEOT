#include "pch.h"
#include "MovableObject.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "Util.h"

MovableObject::MovableObject() : m_velocity(Vec2::Zero), m_speed(1.f), m_collisionCompRef(nullptr)
{

}

void MovableObject::Init(GameState* GameState)
{
	GameplayObject::Init(GameState);
	m_collisionCompRef = GetComponent<CollisionComponent>();
}

void MovableObject::Update(float deltaTime)
{
	/*
	 * Sort of a simple implementation of a Continuous collision detection approach
	 * A movable object moves in the direction of its velocity until it collides with something
	*/
	//evaluate only if object is moving
	if (!GetVelocity().Equals(Vec2::Zero))
	{
		const Vec2 CurrentPos = GetPosition();
		const Vec2 TargetPos = GetPosition() + GetVelocity() * deltaTime * GetSpeed();

		//evaluate step by step only if TargetPos detect a collision
 		if (!CanMove(TargetPos))
		{
			Vec2 PosAfterRestitution = Vec2::Lerp(CurrentPos, TargetPos, deltaTime);
			//if we can't move already neither in current or last pos, stop 
			if(!CanMove(CurrentPos) && !CanMove(PosAfterRestitution)) return;

			for (;;)
			{
				Vec2 NewRestitutionPos = Vec2::Lerp(PosAfterRestitution, TargetPos, deltaTime);
				if (!CanMove(NewRestitutionPos))
				{
					SetPosition(NewRestitutionPos);
					break;
				}
				//New last post is last LerpPos
				PosAfterRestitution = NewRestitutionPos;
			}
		}
		else
		{
			/**
			 * 	no obstacles detected in target pos
			 *  either we tunnelled the obstacle
			 *  or the path is free
			 */
			SetPosition(TargetPos);
		}
	}

	GameplayObject::Update(deltaTime);
}

bool MovableObject::IsBlocker(BaseObject* Object) const
{
	return dynamic_cast<MovableObject*> (Object) || !dynamic_cast<GameplayObject*>(Object);
}

bool MovableObject::CanMove(const Vec2& NewPosition) const
{
	if (NewPosition.Equals(Vec2::Zero)) return true; //its not moving
	if (!m_collisionCompRef) return true;

	std::vector<BaseObject*> collisions;
	std::vector<BaseObject*> ignores;
	m_collisionCompRef->FindCollisionsInPosition(NewPosition, &collisions, &ignores);

	for (BaseObject* collision : collisions)
	{
		if (IsBlocker(collision))
			return false;
	}

	return true;
}

bool MovableObject::IsStandingStill() const
{
	return GetVelocity().Equals(Vec2::Zero);
}
