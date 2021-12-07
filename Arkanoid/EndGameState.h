#pragma once
#include "GameState.h"

class Game;

class EndGameState : public GameState
{
public:
	EndGameState(Game* GameInstance);

	virtual void Update(float deltaTime) override;
	
	void Quit();
	void Restart();

private:
	bool bRequestedQuit;
	bool bRequestedRestart;
};

