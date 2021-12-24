#pragma once
#include "BaseComponent.h"
#include <vector>
#include <map>
#include <functional>

class BaseShape;

class CollisionComponent : public BaseComponent
{
public:
	using CollisionCallback = std::function<void()>;
	using Callbacks = std::map<BaseObject*, CollisionCallback>;
	using ShapeColor = DirectX::XMVECTORF32;
	
	static bool ShouldRenderCollision;

	CollisionComponent(BaseShape* shape);
	~CollisionComponent();

	virtual void Init() override;
	virtual void Render(const RendererData& Renderer) override;
	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;

	bool Intersect(const CollisionComponent& other) const;
	
	std::vector<BaseObject*>& GetCollisions();

	BaseShape* GetShape() const;
	
	/*Returns the Normal at the surface of OtherObject in which we collided*/
	Vec2 GetCollisionNormalWithObject(BaseObject* OtherObject, const Vec2& Velocity) const;
	
	bool FindCollisionsInPosition(const Vec2& Position, std::vector<BaseObject*>* Collisions = nullptr, std::vector<BaseObject*>* Ignores = nullptr);

	void SetShapeColor(ShapeColor Color) {m_shapeColor = Color;}
	ShapeColor GetShapeColor() const { return m_shapeColor; }

	void AddCallback(BaseObject* object, CollisionCallback callback);
	void RemoveCallback(BaseObject* object);

public:
	bool enabled;

private:
	BaseShape* m_shape;
	ShapeColor m_shapeColor;
	std::vector<BaseObject*> m_collisions;

	Callbacks m_callbacks;
};


