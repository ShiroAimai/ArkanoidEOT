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

	/*A convenient routine that attach a Ball object to this one. The attached ball is moved around like a child object*/
	bool StoreBall(Ball* ball);
	/*If a Ball is stored then launch that ball*/
	bool LaunchBall();
private:
	Vec2 m_storedBallAttachOffset;
	Ball* m_storedBall;

private:
	CollisionComponent* m_collisionComp;
	VisualComponent* m_visualComp;
};

