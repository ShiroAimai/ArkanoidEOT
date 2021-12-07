#pragma once
#include "BaseLevel.h"

class EndGameLevel : public BaseLevel
{
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) override;
};

