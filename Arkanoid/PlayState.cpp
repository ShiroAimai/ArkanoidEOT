#include "pch.h"
#include "PlayState.h"
#include "Level1.h"
#include "EndGameState.h"
#include "EndGameLevel.h"

PlayState::PlayState(Game* GameInstance) : GameState(GameInstance), bIsGameOver(false)
{
	m_level = new Level1();
}

void PlayState::Update(float deltaTime)
{
	GameState::Update(deltaTime);
	if (bIsGameOver)
	{
		UpdateGameState(new EndGameState(true, game)); //todo update with game logic
	}
}

void PlayState::GameOver()
{
	bIsGameOver = true;
}
