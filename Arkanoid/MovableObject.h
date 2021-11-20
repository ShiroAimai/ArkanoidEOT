#pragma once
#include "GameplayObject.h"

class MovableObject : public GameplayObject
{
public:
	MovableObject();

	virtual void Init(GameState* GameState) override;
	virtual void Update(float deltaTime) override;

	virtual bool IsBlocker(BaseObject* Object) const;
	virtual bool CanMove(const Vec2& NewPosition) const;

	Vec2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const Vec2& NewVelocity) 
	{ 
		m_velocity = NewVelocity; 
		m_velocity.Normalize();
	};
	float GetSpeed() const { return m_speed; };
	void SetSpeed(float NewSpeed) { m_speed = NewSpeed; };
	
	bool IsStandingStill() const;
private:
	Vec2 m_velocity;
	float m_speed;
	class CollisionComponent* m_collisionCompRef;
};

