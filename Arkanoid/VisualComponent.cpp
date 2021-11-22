#include "pch.h"
#include "VisualComponent.h"
#include "Sprite.h"


VisualComponent::VisualComponent(int width, int height, const vector<Sprite*>& sprites)
 : m_currentRenderSprite(nullptr),
   m_width(width),
   m_height(height),
   m_color(DirectX::Colors::White),
   m_anchor(0.5f, 0.5f)
{
	m_sprites.insert(m_sprites.end(), sprites.begin(), sprites.end());
	m_currentRenderSprite = m_sprites.size() > 0 ? m_sprites[0] : nullptr;
	SetRenderLayer(10);
}

VisualComponent::VisualComponent(Sprite* Sprite)
	: m_currentRenderSprite(Sprite),
	m_width(0),
	m_height(0),
	m_color(DirectX::Colors::White),
	m_anchor(0.5f, 0.5f)
{
	m_sprites.push_back(Sprite);
	SetRenderLayer(10);
}

VisualComponent::~VisualComponent()
{
	for (Sprite* sprite : m_sprites)
	{
		delete sprite;
	}
	m_sprites.clear();
}

void VisualComponent::Update(float deltaTime)
{
	if (m_currentRenderSprite)
	{
		m_currentRenderSprite->Update(deltaTime);
	}
}

void VisualComponent::Render(const RendererData& Renderer)
{
	if(!m_parent) return; //a configuration error
	if(!m_currentRenderSprite) return; //no sprite to render

	int anchorOffsetX = int(m_width * m_anchor.x), anchorOffsetY = int(m_height * m_anchor.y);
	Vec2 origin((float)anchorOffsetX, (float)anchorOffsetY);
	
	float angleInRad = m_parent->GetAngle() * DirectX::XM_PI / 180.f;

	m_currentRenderSprite->Render(Renderer.m_spriteBatch, m_parent->GetPosition(), origin, angleInRad, m_parent->GetScale(), GetRenderLayer(), m_color);
}

void VisualComponent::CreateResources()
{
	for (Sprite* sprite : m_sprites)
		sprite->CreateResources();

	if (m_sprites.size() == 1)
	{
		m_width = m_sprites[0]->GetWidth();
		m_height = m_sprites[0]->GetHeight();
	}
}

void VisualComponent::ReleaseResources()
{
	for(Sprite* sprite : m_sprites)
		sprite->ReleaseResources();
}

void VisualComponent::SetRenderSpriteIndex(int index)
{
	if (index < m_sprites.size() && m_currentRenderSprite != m_sprites[index])
	{
		if (m_currentRenderSprite->IsPlaying())
		{
			m_currentRenderSprite->Stop();
		}
		m_currentRenderSprite = m_sprites[index];
	}
}
