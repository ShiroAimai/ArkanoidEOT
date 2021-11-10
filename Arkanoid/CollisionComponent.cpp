#include "pch.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "GameState.h"

bool CollisionComponent::ShouldRenderCollision = false;

CollisionComponent::CollisionComponent(BaseShape* shape) : m_shape(shape)
{
	SetRenderLayer(10);
	SetUpdatePriority(1);
	m_renderMode = RenderMode::Primitive;
}

CollisionComponent::~CollisionComponent()
{
	if(m_shape)
		delete m_shape;
}

void CollisionComponent::Init()
{
	if(m_shape)
		m_shape->Transform(m_parent->GetTransform());
}

void CollisionComponent::Render(const RendererData& Renderer)
{
	if (ShouldRenderCollision)
	{
		m_shape->Draw(Renderer.m_primitiveBatch);
	}
}

void CollisionComponent::Update(float deltaTime)
{
	m_shape->Transform(m_parent->GetTransform());

	m_collisions.clear();
	GetCollisions();
}

bool CollisionComponent::Intersect(const CollisionComponent& other) const
{
	BaseShape* otherShape = nullptr;
	otherShape = other.GetShape();

	return otherShape != nullptr ? m_shape->intersect(*otherShape) : false;
}

std::vector<BaseObject*>& CollisionComponent::GetCollisions()
{
	if (m_shape)
	{
		std::vector<BaseObject*> ObjectsToIgnore;
		ObjectsToIgnore.push_back(m_parent);

		m_parent->GetGameState<GameState>()->FindCollisions(*this, &m_collisions, &ObjectsToIgnore);
	}
	return m_collisions;
}

BaseShape* CollisionComponent::GetShape() const
{
	return m_shape;
}
