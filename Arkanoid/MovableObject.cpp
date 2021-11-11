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
	SetPosition(GetPosition() + (GetVelocity() * deltaTime * GetSpeed()));
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
	Transform2D MovementProjTrans;
	MovementProjTrans.Set(NewPosition, GetAngle(), GetScale());
	//temporary move collision shape to new position in order to test collisions there
	m_collisionCompRef->GetShape()->Transform(MovementProjTrans);
	std::vector<BaseObject*>& collisions = m_collisionCompRef->GetCollisions();
	//move back to its original position the collision shape
	MovementProjTrans.SetTranslation(GetPosition());
	m_collisionCompRef->GetShape()->Transform(MovementProjTrans);

	for (BaseObject* collision : collisions)
	{
		if(IsBlocker(collision))
			return false;
	}
	
	return true;
}
