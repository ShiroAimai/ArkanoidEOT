#pragma once
#include "GameState.h"

class Game;

class EndGameState : public GameState
{
public:
	static const std::string GameOverLabelId;
	static const std::string ScoreLabelId;

	EndGameState(bool HasWon, Game* GameInstance);

	virtual void Update(float deltaTime) override;
	
	virtual void OnEnter() override;

	void Quit();
	void Restart();

private:
	bool bWin;
	bool bRequestedQuit;
	bool bRequestedRestart;
};

