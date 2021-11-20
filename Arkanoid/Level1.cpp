#include "pch.h"
#include "Level1.h"
#include "PlayerBar.h"
#include "LevelBorder.h"
#include "WorldHelper.h"
#include "Ball.h"
#include "CollisionComponent.h"
#include "PlayState.h"


void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	Ball* ball = new Ball(16.5f);
	Ball& ballref = *ball;
	//ball->SetPosition(Vec2(-300, 250));
	//ball->SetVelocity(Vec2(1, 0));
	ball->SetScale(Vec2(0.8f, 0.8f));

	PlayerBar* player = new PlayerBar;
	player->SetPosition(Vec2(0, 250));
	player->StoreBall(ball);

	GameObjects.push_back(player);
	GameObjects.push_back(ball);

	//level bounds
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
	bottom->GetComponent<CollisionComponent>()->AddCallback(ball, [&ballref] {
		ballref.GetGameState<PlayState>()->GameOver();
	});
	GameObjects.push_back(bottom);

}
