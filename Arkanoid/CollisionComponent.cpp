#include "pch.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "GameState.h"

bool CollisionComponent::ShouldRenderCollision = false;

CollisionComponent::CollisionComponent(BaseShape* shape) : m_shape(shape)
{
	SetRenderLayer(1);
	SetUpdatePriority(1);
}

CollisionComponent::~CollisionComponent()
{
	if(m_shape)
		delete m_shape;
}

void CollisionComponent::Render(DirectX::SpriteBatch* batch)
{
	if (ShouldRenderCollision)
	{
		m_shape->Draw();
	}
}

void CollisionComponent::Update(float deltaTime)
{
	m_collisions.clear();
	if (m_shape)
	{
		std::vector<BaseObject*> ObjectsToIgnore;
		ObjectsToIgnore.push_back(m_parent);

		m_parent->GetGameState<GameState>()->FindCollisions(*this, &m_collisions, &ObjectsToIgnore);
	}
}

bool CollisionComponent::Intersect(const CollisionComponent& other) const
{
	BaseShape* otherShape = nullptr;
	otherShape = other.GetShape();

	return otherShape != nullptr ? m_shape->intersect(*otherShape) : false;
}

std::vector<BaseObject*>& CollisionComponent::GetCollisions()
{
	return m_collisions;
}

BaseShape* CollisionComponent::GetShape() const
{
	return m_shape;
}
