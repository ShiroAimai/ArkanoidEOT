#include "pch.h"
#include "BaseLevel.h"
#include "BaseObject.h"

BaseLevel::~BaseLevel()
{

}

void BaseLevel::Load(GameState* ParentGameState)
{
	std::vector<BaseObject*> GameObjects;
	GetLevelObjects(GameObjects);

	for(BaseObject* obj : GameObjects)
		ParentGameState->AddGameObject(obj);
}
