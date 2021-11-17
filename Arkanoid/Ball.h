#pragma once
#include "MovableObject.h"

class CollisionComponent;

class Ball : public MovableObject
{
public:
	Ball();

	virtual void FixedUpdate() override;
private:
	CollisionComponent* mCollisionComponent;
};

