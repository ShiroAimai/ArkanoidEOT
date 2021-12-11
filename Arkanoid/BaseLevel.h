#pragma once
#include "GameState.h"
#include <vector>

class BaseObject;

class BaseLevel
{
public:
	virtual ~BaseLevel();
	void Load(std::vector<BaseObject*>& LevelObjects);

	virtual DirectX::XMVECTORF32 GetLevelBackground() const = 0;

protected:
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) = 0;
};

