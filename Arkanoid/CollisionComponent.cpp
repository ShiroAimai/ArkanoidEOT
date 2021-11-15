#include "pch.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "GameState.h"

bool CollisionComponent::ShouldRenderCollision = false;

CollisionComponent::CollisionComponent(BaseShape* shape) : m_shape(shape), m_shapeColor(DirectX::Colors::Red)
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
		m_shape->Draw(Renderer.m_primitiveBatch, m_shapeColor);
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

Vec2 CollisionComponent::GetCollisionNormalWithObject(BaseObject* OtherObject, const Vec2& Velocity) const
{
	if (std::find(m_collisions.begin(), m_collisions.end(), OtherObject) == m_collisions.end())
		return Vec2::Zero; // non valid collision normal
	
	CollisionComponent* OtherComp = OtherObject->GetComponent<CollisionComponent>();
	
	return OtherComp != nullptr ? m_shape->GetCollisionNormal(*OtherComp->GetShape(), Velocity) : Vec2::Zero;
}

