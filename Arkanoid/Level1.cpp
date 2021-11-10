#include "pch.h"
#include "Level1.h"
#include "PlayerBar.h"
#include "LevelBorder.h"
#include "WorldHelper.h"


void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	PlayerBar* player = new PlayerBar;
	player->SetPosition(Vec2(200, 200));
	GameObjects.push_back(player);
	
	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	long halfWidth = bounds.right / 2;
	long halfHeight = bounds.bottom / 2;
	LevelBorder* left = new LevelBorder(Vec2(0, halfHeight), Vec2(0, -halfHeight));
	left->SetPosition(Vec2(-halfWidth + 1, 0));
	GameObjects.push_back(left);
	LevelBorder* right = new LevelBorder(Vec2(0, -halfHeight), Vec2(0, halfHeight));
	right->SetPosition(Vec2(halfWidth - 1, 0));
	GameObjects.push_back(right);
}
