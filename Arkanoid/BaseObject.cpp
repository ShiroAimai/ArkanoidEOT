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

void BaseObject::Render(vector<BaseComponent*>& renderables)
{
	for (BaseComponent* component : m_components)
	{
		if (component->getRenderLayer() > 0)
			renderables.push_back(component);
	}
}

void BaseObject::AddComponent(BaseComponent* component)
{
	if(!component) return; //no valid component
	component->SetParent(this);
	std::vector<BaseComponent*>::iterator itt = m_components.begin();
	for (; itt != m_components.end(); itt++)
	{
		if ((*itt)->getUpdatePriority() >= component->getUpdatePriority())
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
