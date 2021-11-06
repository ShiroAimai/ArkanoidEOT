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

	Vec2 GetSpeed() const { return m_speed; };
	void SetSpeed(const Vec2& NewSpeed) { m_speed = NewSpeed; };
private:
	Vec2 m_speed;
	class CollisionComponent* m_collisionCompRef;
};

