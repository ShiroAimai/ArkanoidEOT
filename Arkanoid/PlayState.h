#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	PlayState();
	
	void GameOver();

	virtual void OnEnter() override;
	virtual void OnExit() override;
};

