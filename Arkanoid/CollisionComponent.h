#pragma once
#include "BaseComponent.h"
#include <vector>

class BaseShape;

class CollisionComponent : public BaseComponent
{
public:
	using ShapeColor = DirectX::XMVECTORF32;
	static bool ShouldRenderCollision;

	CollisionComponent(BaseShape* shape);
	~CollisionComponent();

	virtual void Init() override;
	virtual void Render(const RendererData& Renderer) override;
	virtual void Update(float deltaTime) override;

	bool Intersect(const CollisionComponent& other) const;
	std::vector<BaseObject*>& GetCollisions();

	BaseShape* GetShape() const;
	Vec2 GetCollisionNormalWithObject(BaseObject* OtherObject, const Vec2& Velocity) const;

	void SetShapeColor(ShapeColor Color) {m_shapeColor = Color;}
	ShapeColor GetShapeColor() const { return m_shapeColor; }
private:
	BaseShape* m_shape;
	ShapeColor m_shapeColor;
	std::vector<BaseObject*> m_collisions;
	std::vector<BaseObject*> m_ignoredObjects;
};


