#include "pch.h"
#include "Level1.h"
#include "BaseObject.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "TextComponent.h"

void Level1::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	BaseObject* m_obj = new BaseObject();
	Sprite* sprite = Sprite::Load(L"Assets/cat.png");
	VisualComponent* vc = new VisualComponent(sprite);
	m_obj->AddComponent(vc);

	GameObjects.push_back(m_obj);
}
