#include "pch.h"
#include "BaseLevel.h"
#include "BaseObject.h"

BaseLevel::~BaseLevel()
{

}

void BaseLevel::Load(std::vector<BaseObject*>& LevelObjects)
{
	GetLevelObjects(LevelObjects);
}
