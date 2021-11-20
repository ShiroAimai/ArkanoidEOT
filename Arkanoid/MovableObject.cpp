#include "pch.h"
#include "MovableObject.h"
#include "CollisionComponent.h"
#include "Collision.h"

namespace {
	float LerpFindingAdjustedPosStep = 0.1f;
}

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
	//evaluate only if ball is moving
	if (!GetVelocity().Equals(Vec2::Zero))
	{
		const Vec2 CurrentPos = GetPosition();
		const Vec2 TargetPos = GetPosition() + GetVelocity() * deltaTime * GetSpeed();

		//evaluate step by step only if TargetPos detect a collision
		if (!CanMove(TargetPos))
		{
			Vec2 LastPos = Vec2::Lerp(CurrentPos, TargetPos, LerpFindingAdjustedPosStep);
			for (;;)
			{
				Vec2 LerpPos = Vec2::Lerp(LastPos, TargetPos, deltaTime);
				if (!CanMove(LerpPos))
				{
					SetPosition(LerpPos);
					std::string out = "LerpPos X" + std::to_string(LerpPos.x) + "Y " + std::to_string(LerpPos.y);
					OutputDebugStringA(out.c_str());
					break;
				}
				//New last post is last LerpPos
				LastPos = LerpPos;
			}
		}
		else
		{
			SetPosition(TargetPos);
			std::string out = "TargetPos X" + std::to_string(TargetPos.x) + "Y " + std::to_string(TargetPos.y);
			OutputDebugStringA(out.c_str());
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
