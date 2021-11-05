#include "pch.h"
#include "BaseObject.h"
#include "GameState.h"
#include "BaseComponent.h"


BaseObject::BaseObject()
{
	m_transform.SetIdentity();
}

void BaseObject::Init(GameState* GameState)
{
	m_gameState = GameState;
	for (BaseComponent* component : m_components)
	{
		component->Init();
	}
}

void BaseObject::Uninit()
{
	for (BaseComponent* component : m_components)
	{
		component->Uninit();
	}
}

void BaseObject::Update(float deltaTime)
{
	for (BaseComponent* component : m_components)
	{
		component->Update(deltaTime);
	}
}

void BaseObject::Render(DirectX::SpriteBatch* batch)
{
	for (BaseComponent* component : m_components)
	{
		component->Render(batch);
	}
}

void BaseObject::OnCreateResources()
{
	for(BaseComponent* Comp : m_components)
		Comp->OnCreateResources();
}

void BaseObject::OnReleaseResources()
{
	for (BaseComponent* Comp : m_components)
		Comp->OnReleaseResources();
}

void BaseObject::AddComponent(BaseComponent* component)
{
	if(!component) return; //no valid component
	component->SetParent(this);
	std::vector<BaseComponent*>::iterator itt = m_components.begin();
	for (; itt != m_components.end(); itt++)
	{
		if ((*itt)->GetUpdatePriority() <= component->GetUpdatePriority())
		{
			m_components.insert(itt, component);
			break;
		}
	}
}

void BaseObject::SetGameState(GameState* gameState)
{
	m_gameState = gameState; 
}

BaseObject::~BaseObject()
{
	for (BaseComponent* comp : m_components)
	{
		delete comp;
	}
	m_components.clear();
}
