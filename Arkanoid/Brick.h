#pragma once
#include "GameplayObject.h"
#include "BrickConfig.h"

class CollisionComponent;
class VisualComponent;

class Brick : public GameplayObject
{
public:
	Brick(BrickType type);
	
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	/*Returns the remaining life points for this brick*/
	int GetLifePoints() const { return m_config->m_lifePoints;}
	/*Returns the color of this brick*/
	DirectX::XMVECTORF32 GetColor() const { return m_config->m_color; }
	
	/*Override BrickType */
	void SetBrickType(BrickType type);
	
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

