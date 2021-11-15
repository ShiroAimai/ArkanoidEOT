#include "pch.h"
#include "Level1.h"
#include "PlayerBar.h"
#include "LevelBorder.h"
#include "WorldHelper.h"
#include "Ball.h"


void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	PlayerBar* player = new PlayerBar;
	GameObjects.push_back(player);
	
	Ball* ball = new Ball;
	ball->SetPosition(Vec2(-200, -200));
	GameObjects.push_back(ball);

	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	long halfWidth = bounds.right / 2;
	long halfHeight = bounds.bottom / 2;
	LevelBorder* left = new LevelBorder(Vec2(0, halfHeight), Vec2(0, -halfHeight));
	left->SetPosition(Vec2(-halfWidth + 1, 0));
	GameObjects.push_back(left);
	LevelBorder* right = new LevelBorder(Vec2(0, -halfHeight), Vec2(0, halfHeight));
	right->SetPosition(Vec2(halfWidth - 1, 0));
	GameObjects.push_back(right);
	LevelBorder* top = new LevelBorder(Vec2(-halfWidth, 0), Vec2(halfWidth, 0));
	top->SetPosition(Vec2(0, -halfHeight + 1));
	GameObjects.push_back(top);
	LevelBorder* bottom = new LevelBorder(Vec2(-halfWidth, 0), Vec2(halfWidth, 0));
	bottom->SetPosition(Vec2(0, halfHeight - 1));
	GameObjects.push_back(bottom);
}
