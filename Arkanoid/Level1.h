#pragma once
#include "BaseLevel.h"

class Level1 : public BaseLevel
{
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) override;
};

