#pragma once
#include "GameState.h"
#include <vector>

class BaseObject;

class BaseLevel
{
public:
	void Load(GameState* ParentGameState);

protected:
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) = 0;
};

