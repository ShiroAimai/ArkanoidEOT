#pragma once
#include "GameState.h"

class Game;
class PlayState : public GameState
{
public:
	PlayState(Game* GameInstance);
	
	virtual void Update(float deltaTime) override;

	void GameOver();

private:
	bool bIsGameOver;
};

