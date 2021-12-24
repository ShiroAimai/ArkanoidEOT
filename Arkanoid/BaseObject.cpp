#include "pch.h"
#include "BaseObject.h"
#include "GameState.h"
#include "BaseComponent.h"


BaseObject::BaseObject() : m_pendingDelete(false)
{
	m_transform.SetIdentity();
}

BaseObject::~BaseObject()
{
	for (BaseComponent* comp : m_components)
	{
		delete comp;
	}
	m_components.clear();
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

void BaseObject::FixedUpdate()
{
	for (BaseComponent* component : m_components)
	{
		component->FixedUpdate();
	}
}

void BaseObject::Update(float deltaTime)
{
	for (BaseComponent* component : m_components)
	{
		component->Update(deltaTime);
	}
}

void BaseObject::Render(std::vector<BaseComponent*>& RenderableSprites, std::vector<BaseComponent*>& RenderablePrimitives)
{
	for (BaseComponent* component : m_components)
	{
		RenderMode CurrentCompRenderMode = component->GetRenderMode();

		switch (CurrentCompRenderMode)
		{
		case RenderMode::Sprite:
			RenderableSprites.push_back(component);
			break;
		case RenderMode::Primitive:
			RenderablePrimitives.push_back(component);
			break;
		}
	}
}

void BaseObject::CreateResources()
{
	for(BaseComponent* Comp : m_components)
		Comp->CreateResources();
}

void BaseObject::ReleaseResources()
{
	for (BaseComponent* Comp : m_components)
		Comp->ReleaseResources();
}

void BaseObject::OnWindowSizeUpdate(float xRatio, float yRatio)
{
	Vec2 NewPos = GetPosition();
	NewPos.x *= xRatio;
	NewPos.y *= yRatio;
	SetPosition(NewPos);

	Vec2 NewScale = GetScale();
	NewScale.x *= xRatio;
	NewScale.y *= yRatio;
	SetScale(NewScale);
}

void BaseObject::AddComponent(BaseComponent* component)
{
	if(!component) return; //no valid component
	component->SetParent(this);
	std::vector<BaseComponent*>::iterator itt = m_components.begin();
	for (; itt != m_components.end(); itt++)
	{
		if ((*itt)->GetUpdatePriority() >= component->GetUpdatePriority())
			break;
	}
	m_components.insert(itt, component);
}

void BaseObject::SetGameState(GameState* gameState)
{
	m_gameState = gameState; 
}
