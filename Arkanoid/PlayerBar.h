#pragma once
#include "MovableObject.h"

class PlayerBar : public MovableObject
{
public:
	PlayerBar();
	virtual void Update(float deltaTime) override;

};

