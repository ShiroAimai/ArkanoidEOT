#include "pch.h"
#include "BaseComponent.h"
#include "BaseObject.h"

BaseComponent::BaseComponent() : m_parent(nullptr)
{

}

BaseComponent::~BaseComponent()
{

}

void BaseComponent::SetParent(BaseObject* NewParent)
{
	m_parent = NewParent;
}

void BaseComponent::Init()
{

}

void BaseComponent::Uninit()
{

}

void BaseComponent::Render()
{

}

void BaseComponent::Update(float deltaTime)
{

}
