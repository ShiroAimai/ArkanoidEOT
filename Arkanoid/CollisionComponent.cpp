#include "pch.h"
#include "CollisionComponent.h"
#include "Collision.h"
#include "GameState.h"

bool CollisionComponent::ShouldRenderCollision = false;

CollisionComponent::CollisionComponent(BaseShape* shape) : m_shape(shape), m_shapeColor(DirectX::Colors::Red), enabled(true)
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

void CollisionComponent::FixedUpdate()
{
	m_collisions.clear();
	if (m_shape)
	{
		std::vector<BaseObject*> ObjectsToIgnore;
		ObjectsToIgnore.push_back(m_parent);

		m_parent->GetGameState<GameState>()->FindCollisions(*this, &m_collisions, &ObjectsToIgnore);
	}
}

void CollisionComponent::Update(float deltaTime)
{
	m_shape->Transform(m_parent->GetTransform());

	for (BaseObject* Collision : m_collisions)
	{
		auto it = m_callbacks.find(Collision);
		if (it != m_callbacks.end())
		{
			it->second();
		}
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

Vec2 CollisionComponent::GetCollisionNormalWithObject(BaseObject* OtherObject, const Vec2& Velocity) const
{
	if (std::find(m_collisions.begin(), m_collisions.end(), OtherObject) == m_collisions.end())
		return Vec2::Zero; // non valid collision normal
	
	CollisionComponent* OtherComp = OtherObject->GetComponent<CollisionComponent>();
	
	return OtherComp != nullptr ? m_shape->GetCollisionNormal(*OtherComp->GetShape(), Velocity) : Vec2::Zero;
}

bool CollisionComponent::FindCollisionsInPosition(const Vec2& Position, std::vector<BaseObject*>* Collisions /*= nullptr*/, std::vector<BaseObject*>* Ignores /*= nullptr*/)
{
	Transform2D MovementProjTrans;
	MovementProjTrans.Set(Position, m_parent->GetAngle(), m_parent->GetScale());
	//temporary move collision shape to new position in order to test collisions there
	m_shape->Transform(MovementProjTrans);

	if (m_shape)
	{
		if (Ignores && std::find(Ignores->begin(), Ignores->end(), m_parent) == Ignores->end())
		{
			Ignores->push_back(m_parent);
		}

		m_parent->GetGameState<GameState>()->FindCollisions(*this, Collisions, Ignores);
	}

	//move back to its original position the collision shape
	MovementProjTrans.SetTranslation(m_parent->GetPosition());
	m_shape->Transform(MovementProjTrans);

	return Collisions && Collisions->size() > 0;
}

void CollisionComponent::AddCallback(BaseObject* object, CollisionCallback callback)
{
	m_callbacks.insert(std::pair<BaseObject*, CollisionCallback>(object, callback));
}

void CollisionComponent::RemoveCallback(BaseObject* object)
{
	auto it = m_callbacks.find(object);
	if (it != m_callbacks.end())
	{
		m_callbacks.erase(it);
	}
}

