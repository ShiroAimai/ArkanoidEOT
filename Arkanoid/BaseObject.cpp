#include "pch.h"
#include "BaseObject.h"
#include "BaseComponent.h"

BaseObject::BaseObject()
{
	m_transform.SetIdentity();
}

void BaseObject::Init()
{
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

void BaseObject::AddComponent(BaseComponent* component)
{
	if(!component) return; //no valid component
	component->SetParent(this);
	std::vector<BaseComponent*>::iterator itt = m_components.begin();
	for (; itt != m_components.end(); itt++)
	{
		if ((*itt)->GetUpdatePriority() >= component->GetUpdatePriority())
		{
			break;
		}
	}
	m_components.insert(itt, component);
}

BaseObject::~BaseObject()
{
	for (BaseComponent* comp : m_components)
	{
		delete comp;
	}
	m_components.clear();
}
