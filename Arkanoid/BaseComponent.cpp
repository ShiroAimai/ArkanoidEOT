#include "pch.h"
#include "BaseComponent.h"
#include "BaseObject.h"

BaseComponent::BaseComponent() : m_parent(nullptr), m_renderLayer(-1.f)
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

void BaseComponent::Render(DirectX::SpriteBatch* batch)
{

}

void BaseComponent::Update(float deltaTime)
{

}

void BaseComponent::SetRenderLayer(uint8_t Layer)
{
	static float MaxLayer = std::numeric_limits<uint8_t>::max();
	m_renderLayer = float(Layer) / MaxLayer;
}
