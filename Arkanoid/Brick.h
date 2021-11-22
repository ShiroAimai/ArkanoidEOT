#pragma once
#include "GameplayObject.h"

class CollisionComponent;
class VisualComponent;

class Brick : public GameplayObject
{
public:
	Brick(int width, int height);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
private:
	int m_width, m_height;
	CollisionComponent* m_collisionComp;
	VisualComponent* m_visualComp;
};

