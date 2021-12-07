#pragma once
#include "GameState.h"

class Game;
class PlayState : public GameState
{
public:
	PlayState(Game* GameInstance);
	
	void GameOver();

	virtual void OnEnter() override;
	virtual void OnExit() override;
};

