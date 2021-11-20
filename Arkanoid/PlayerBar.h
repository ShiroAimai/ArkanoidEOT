#pragma once
#include "MovableObject.h"

class Ball;
class CollisionComponent;
class VisualComponent;

class PlayerBar : public MovableObject
{
public:
	PlayerBar();
	
	virtual void Update(float deltaTime) override;

	bool StoreBall(Ball* ball);
	bool LaunchBall();
private:
	Vec2 m_storedBallAttachOffset;
	Ball* m_storedBall;

private:
	CollisionComponent* m_collisionComp;
	VisualComponent* m_visualComp;
};

