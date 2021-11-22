#include "pch.h"
#include "Level1.h"
#include "PlayerBar.h"
#include "LevelBorder.h"
#include "WorldHelper.h"
#include "Ball.h"
#include "CollisionComponent.h"
#include "PlayState.h"
#include "Brick.h"

namespace {
	long BrickHorizontalDistanceFromBorder = 100L;
	long BrickVerticalDistanceFromBorder = 50L;
	long BrickHorizontalOffset = 11L;
	long BrickVerticalOffset = 10L;
}

void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	Ball* ball = new Ball(16.5f);
	Ball& ballref = *ball;
	ball->SetScale(Vec2(0.8f, 0.8f));

	PlayerBar* player = new PlayerBar;
	player->SetPosition(Vec2(0, 260));
	player->StoreBall(ball);

	GameObjects.push_back(player);
	GameObjects.push_back(ball);

	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	float halfWidth = bounds.right / 2.f;
	float halfHeight = bounds.bottom / 2.f;

	//brick init
	float xCurrent = -halfWidth + BrickHorizontalDistanceFromBorder;
	float yCurrent = -halfHeight + BrickVerticalDistanceFromBorder;
	for (int i = 0; i < 27; ++i)
	{
		if (xCurrent > (halfWidth - BrickHorizontalDistanceFromBorder))
		{
			xCurrent = -halfWidth + BrickHorizontalDistanceFromBorder;
			yCurrent += BrickVerticalOffset + 24;
		}

		Brick* brick = new Brick(64, 24); //Todo define in some other file
		brick->SetPosition(Vec2(xCurrent, yCurrent));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(ball, [&ballref, &brickRef] { brickRef.GetGameState<PlayState>()->RemoveGameObject(&brickRef); });
		}
		GameObjects.push_back(brick);

		xCurrent += brick->GetWidth() + BrickHorizontalOffset;
	}

	//level bounds
	
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
