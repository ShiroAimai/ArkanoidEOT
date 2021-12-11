#pragma once
#include "GameplayObject.h"
#include "BrickConfig.h"

class CollisionComponent;
class VisualComponent;

class Brick : public GameplayObject
{
public:
	Brick(int width, int height, BrickType type);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	int GetLifePoints() const { return m_config->m_lifePoints;}
	DirectX::XMVECTORF32 GetColor() const { return m_config->m_color; }

	/*
	 * Handles brick hit. It manages the change of internal config properties like lifePoints and color
	*/
	void Hit();
private:
	int m_width, m_height;
	
	std::shared_ptr<BrickConfig> m_config;

	CollisionComponent* m_collisionComp;
	VisualComponent* m_visualComp;
};

