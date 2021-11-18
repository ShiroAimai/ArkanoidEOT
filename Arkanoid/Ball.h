#pragma once
#include "MovableObject.h"

class CollisionComponent;
class VisualComponent;

class Ball : public MovableObject
{
public:
	Ball(float radius);

	virtual void FixedUpdate() override;

	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() const { return m_radius;}
private:
	float m_radius;
	VisualComponent* m_visualComp;
	CollisionComponent* m_collisionComp;
};

