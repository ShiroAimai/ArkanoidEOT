#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	PlayState();

	virtual void OnEnter() override;
	virtual void OnExit() override;
};

