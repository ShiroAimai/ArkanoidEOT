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
	m_components.push_back(component);
}

BaseObject::~BaseObject()
{
	for (BaseComponent* comp : m_components)
	{
		delete comp;
	}
	m_components.clear();
}
