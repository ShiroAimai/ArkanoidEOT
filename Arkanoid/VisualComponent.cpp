#include "pch.h"
#include "VisualComponent.h"
#include "Sprite.h"


VisualComponent::VisualComponent(int width, int height, const vector<Sprite*>& sprites)
 : m_currentRenderSprite(nullptr),
   m_width(width),
   m_height(height),
   m_anchor(0.5f, 0.5f),
   m_renderLayer(10)
{
	m_sprites.insert(m_sprites.end(), sprites.begin(), sprites.end());
	m_currentRenderSprite = m_sprites.size() > 0 ? m_sprites[0] : nullptr;
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

void VisualComponent::Render(DirectX::SpriteBatch* batch)
{
	if(!m_parent) return; //a configuration error
	if(!m_currentRenderSprite) return; //no sprite to render
	Vec2 Pos = m_parent->GetPosition();
	int anchorOffsetX = int(m_width * m_anchor.x), anchorOffsetY = int(m_height * m_anchor.y);
	Pos.x -= anchorOffsetX;
	Pos.y -= anchorOffsetY;
	m_currentRenderSprite->Render(batch, Pos, Vec2(anchorOffsetX, anchorOffsetY), m_parent->GetAngle(), m_parent->GetScale());
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
