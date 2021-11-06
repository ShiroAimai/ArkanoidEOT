#include "pch.h"
#include "MovableObject.h"
#include "CollisionComponent.h"

MovableObject::MovableObject() : m_speed(Vec2::Zero)
{

}

void MovableObject::Init(GameState* GameState)
{
	GameplayObject::Init(GameState);
	m_collisionCompRef = GetComponent<CollisionComponent>();
}

void MovableObject::Update(float deltaTime)
{
	SetPosition(GetPosition() + (GetSpeed() * deltaTime));
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
	return true;
}
