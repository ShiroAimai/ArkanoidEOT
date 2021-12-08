#pragma once
#include "GameState.h"

class Game;
class PlayState : public GameState
{
public:
	PlayState(Game* GameInstance);
	
	virtual void OnEnter() override;
	virtual void RemoveGameObject(BaseObject* object, bool doDelete = true);
	virtual void Update(float deltaTime) override;

	void GameOver();

private:
	int m_bricksCount;
	bool bIsGameOver;
};

