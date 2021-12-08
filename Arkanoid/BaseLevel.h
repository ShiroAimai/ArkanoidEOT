#pragma once
#include "GameState.h"
#include <vector>

class BaseObject;

class BaseLevel
{
public:
	virtual ~BaseLevel();
	void Load(std::vector<BaseObject*>& LevelObjects);

protected:
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) = 0;
};

