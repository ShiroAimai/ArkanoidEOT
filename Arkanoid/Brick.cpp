#include "pch.h"
#include "Brick.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "VisualComponent.h"
#include "Sprite.h"
#include "GameState.h"

Brick::Brick(BrickType type) 
: m_width(0), 
  m_height(0), 
  m_config(BrickHelper::Instance()->GetBrickConfigByType(type))
{
	Sprite* sprite = Sprite::LoadStatic("brick", L"Assets/brick.png");
	m_visualComp = new VisualComponent(sprite);
	m_visualComp->SetColor(m_config->m_color);
	AddComponent(m_visualComp);

	m_width = m_visualComp->GetWidth();
	m_height = m_visualComp->GetHeight();

	float halfWidth = m_width / 2.f;
	float halfHeight = m_height / 2.f;
	Shape<AABB>* box = new Shape<AABB>();
	box->m_originalShape.m_min = Vec2(-halfWidth, -halfHeight);
	box->m_originalShape.m_max = Vec2(halfWidth, halfHeight);
	m_collisionComp = new CollisionComponent(box);
	m_collisionComp->SetShapeColor(DirectX::Colors::Violet);
	AddComponent(m_collisionComp);

}

void Brick::SetBrickType(BrickType type)
{
	m_config = BrickHelper::Instance()->GetBrickConfigByType(type);
	if (m_config)
	{
		m_visualComp->SetColor(m_config->m_color);
	}
}

void Brick::Hit()
{
	m_config = BrickHelper::Instance()->GetBrickConfigByLifePoints(GetLifePoints() - 1);
	if (m_config)
	{
		m_visualComp->SetColor(m_config->m_color);
	}

	//handle death
	if (!m_config)
	{
		GetGameState<GameState>()->RemoveGameObject(this);
	}

}
