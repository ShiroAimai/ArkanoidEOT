#pragma once
#include "BaseComponent.h"
#include <vector>

class BaseShape;

class CollisionComponent : public BaseComponent
{
public:
	static bool ShouldRenderCollision;

	CollisionComponent(BaseShape* shape);
	~CollisionComponent();

	virtual void Init() override;
	virtual void Render(const RendererData& Renderer) override;
	virtual void Update(float deltaTime) override;

	bool Intersect(const CollisionComponent& other) const;
	std::vector<BaseObject*>& GetCollisions();

	BaseShape* GetShape() const;
	
private:
	BaseShape* m_shape;
	std::vector<BaseObject*> m_collisions;
	std::vector<BaseObject*> m_ignoredObjects;
};

