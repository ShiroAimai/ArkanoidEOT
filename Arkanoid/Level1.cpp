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
	long BrickVerticalOffset = 34L;
}

void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	Ball* ball = new Ball(12.5f);
	ball->SetId("ball");

	PlayerBar* player = new PlayerBar;
	player->SetPosition(Vec2(0, 260));
	player->StoreBall(ball);
	player->SetId("player");

	GameObjects.push_back(player);
	GameObjects.push_back(ball);

	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	float halfWidth = bounds.right / 2.f;
	float halfHeight = bounds.bottom / 2.f;

	GetRandomLevel(ball, GameObjects);

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

	Ball& ballRef = *ball;
	bottom->GetComponent<CollisionComponent>()->AddCallback(ball, [&ballRef] {
		ballRef.GetGameState<PlayState>()->GameOver();
	});
	GameObjects.push_back(bottom);

}

void Level1::GetRandomLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects)
{
	//simple random index generator in range [0, 9]
	srand((unsigned)time(NULL));
	int index = rand() % 10;

	if (index < 4)
	{
		GetEasyLevel(LevelBall, GameObjects);
		return;
	}

	if (index < 8)
	{
		GetNormalLevel(LevelBall, GameObjects);
		return;
	}

	GetHardLevel(LevelBall, GameObjects);
}

void Level1::GetEasyLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects)
{
	static int EasyLevelBricks = 27;

	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	float halfWidth = bounds.right / 2.f;
	float halfHeight = bounds.bottom / 2.f;

	float xInitial = -halfWidth + BrickHorizontalDistanceFromBorder;
	float x = xInitial;
	float y = -halfHeight + BrickVerticalDistanceFromBorder;

	//1 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Red);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//2 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Red);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//3 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Red);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}
}

//red bricks only in the first and last column, and first and last row
//yellow bricks in the other ones
void Level1::GetNormalLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects)
{
	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	float halfWidth = bounds.right / 2.f;
	float halfHeight = bounds.bottom / 2.f;

	float xInitial = -halfWidth + BrickHorizontalDistanceFromBorder;
	float x = xInitial;
	float y = -halfHeight + BrickVerticalDistanceFromBorder;

	//1 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Red);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//2 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Yellow);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;

		if (column == 0 || x > (halfWidth - BrickHorizontalDistanceFromBorder))
		{
			brick->SetBrickType(BrickType::Red);
		}
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//3 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Red);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}
}


void Level1::GetHardLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects)
{
	RECT bounds = WorldHelper::Instance()->GetGameBounds();
	float halfWidth = bounds.right / 2.f;
	float halfHeight = bounds.bottom / 2.f;

	float xInitial = -halfWidth + BrickHorizontalDistanceFromBorder;
	float x = xInitial;
	float y = -halfHeight + BrickVerticalDistanceFromBorder;

	//1 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Blue);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//2 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Yellow);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;

		if (column == 0 || x > (halfWidth - BrickHorizontalDistanceFromBorder))
		{
			brick->SetBrickType(BrickType::Blue);
		}
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//3 row
	//2 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Yellow);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;

		if (column == 0 || x > (halfWidth - BrickHorizontalDistanceFromBorder))
		{
			brick->SetBrickType(BrickType::Blue);
		}
	}

	x = xInitial;
	y += BrickVerticalOffset;

	//4 row
	for (int column = 0; x <= (halfWidth - BrickHorizontalDistanceFromBorder); ++column)
	{
		Brick* brick = new Brick(BrickType::Blue);
		brick->SetPosition(Vec2(x, y));
		CollisionComponent* brickCc = brick->GetComponent<CollisionComponent>();
		if (brickCc)
		{
			Brick& brickRef = *brick;
			brickCc->AddCallback(LevelBall, [&brickRef] { brickRef.Hit(); });
		}
		GameObjects.push_back(brick);
		x += brick->GetWidth() + BrickHorizontalOffset;
	}

}
