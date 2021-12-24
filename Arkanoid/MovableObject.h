#pragma once
#include "GameplayObject.h"

/*Models a movable Gameplay object*/
class MovableObject : public GameplayObject
{
public:
	MovableObject();

	virtual void Init(GameState* GameState) override;
	virtual void Update(float deltaTime) override;
	
	/*Defines which objects can block this MovableObject*/
	virtual bool IsBlocker(BaseObject* Object) const;
	
	/*Useful routine to check for collision in a specific location*/
	virtual bool CanMove(const Vec2& NewPosition) const;

	/*Returns the velocity vector*/
	Vec2 GetVelocity() const { return m_velocity; };
	
	/*Override the velocity vector*/
	void SetVelocity(const Vec2& NewVelocity) 
	{ 
		m_velocity = NewVelocity; 
		m_velocity.Normalize();
	};

	/*Returns the speed multiplier*/
	float GetSpeed() const { return m_speed; };
	
	/*Override the speed multiplier*/
	void SetSpeed(float NewSpeed) { m_speed = NewSpeed; };
	
	/*Returns a value indicating if the Movable is not moving*/
	bool IsStandingStill() const;
private:
	Vec2 m_velocity;
	float m_speed;
	class CollisionComponent* m_collisionCompRef;
};

