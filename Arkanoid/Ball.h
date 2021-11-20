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
	float GetRadius() const { 
		Vec2 Scale = GetScale();
		assert(Scale.x == Scale.y);
		return m_radius * Scale.x;
	}
private:
	float m_radius;
	VisualComponent* m_visualComp;
	CollisionComponent* m_collisionComp;
};

