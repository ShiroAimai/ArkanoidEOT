#include "pch.h"
#include "EndGameState.h"
#include "Game.h"
#include "EndGameLevel.h"

EndGameState::EndGameState(Game* GameInstance) 
: GameState(GameInstance),
bRequestedQuit(false),
bRequestedRestart(false)
{
	m_level = new EndGameLevel();
}

void EndGameState::Update(float deltaTime)
{
	GameState::Update(deltaTime);

	if (bRequestedQuit)
	{
		game->Quit();
		return;
	}
	
	if (bRequestedRestart)
	{
		UpdateGameState(new PlayState(game));
	}
}

void EndGameState::Quit()
{
	bRequestedQuit = true;
}

void EndGameState::Restart()
{
	bRequestedRestart = true;
}
