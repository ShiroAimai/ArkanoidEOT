#pragma once
#include "MovableObject.h"

class CollisionComponent;

class Ball : public MovableObject
{
public:
	Ball();

	virtual void Update(float deltaTime) override;
private:
	CollisionComponent* mCollisionComponent;
};

