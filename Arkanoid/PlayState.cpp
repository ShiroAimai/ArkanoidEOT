#include "pch.h"
#include "PlayState.h"
#include "Level1.h"
#include "EndGameState.h"
#include "EndGameLevel.h"
#include "Brick.h"

PlayState::PlayState(Game* GameInstance) : GameState(GameInstance), bIsGameOver(false), m_bricksCount(0)
{
	m_level = new Level1();
}


void PlayState::OnEnter()
{
	GameState::OnEnter();
	std::vector<BaseObject*>& GameObjects = GetGameObjects();

	for (BaseObject* object : GameObjects)
	{
		if (dynamic_cast<Brick*>(object) != nullptr)
		{
			++m_bricksCount;
		}
	}
}

void PlayState::RemoveGameObject(BaseObject* object, bool doDelete /*= true*/)
{
	//before removing object check if it is a brick, if it is decrement counter
	if (dynamic_cast<Brick*>(object) != nullptr)
	{
		--m_bricksCount;
		if (m_bricksCount == 0)
		{
			bIsGameOver = true; //player destroyed last brick, so he won
		}
	}
	GameState::RemoveGameObject(object, doDelete);
}

void PlayState::Update(float deltaTime)
{
	GameState::Update(deltaTime);
	if (bIsGameOver)
	{
		UpdateGameState(new EndGameState(m_bricksCount == 0, game));
	}
}

void PlayState::GameOver()
{
	bIsGameOver = true;
}
