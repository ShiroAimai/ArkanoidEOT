#include "pch.h"
#include "Level1.h"
#include "PlayerBar.h"


void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	PlayerBar* player = new PlayerBar;
	GameObjects.push_back(player);

	PlayerBar* player2 = new PlayerBar;
	player2->SetPosition(Vec2(250, 250));
	GameObjects.push_back(player2);

}
