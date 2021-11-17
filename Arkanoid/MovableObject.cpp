#include "pch.h"
#include "MovableObject.h"
#include "CollisionComponent.h"
#include "Collision.h"

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
	Vec2 NewPos = GetPosition() + (GetVelocity() * deltaTime * GetSpeed());
	SetPosition(NewPos);
	GameplayObject::Update(deltaTime);
}

bool MovableObject::IsBlocker(BaseObject* Object) const
{
	return dynamic_cast<MovableObject*> (Object) || !dynamic_cast<GameplayObject*>(Object);
}

bool MovableObject::CanMove(const Vec2& NewPosition) const
{
	if(NewPosition.Equals(Vec2::Zero)) return true; //its not moving
	if(!m_collisionCompRef) return true;

	std::vector<BaseObject*> collisions;
	std::vector<BaseObject*> ignores;
	m_collisionCompRef->FindCollisionsInPosition(NewPosition, &collisions, &ignores);

	for (BaseObject* collision : collisions)
	{
		if(IsBlocker(collision))
			return false;
	}
	
	return true;
}
