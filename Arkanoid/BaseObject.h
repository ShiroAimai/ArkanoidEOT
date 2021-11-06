#pragma once
#include <vector>
#include "Transform2D.h"
#include "RendererData.h"

using std::vector;

class GameState;
class BaseComponent;

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();
	
	BaseObject(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&) = delete;

	virtual void Init(GameState* GameState);
	virtual void Uninit();
	virtual void Update(float deltaTime);
	virtual void Render(std::vector<BaseComponent*>& RenderableSprites, std::vector<BaseComponent*>& RenderablePrimitives);

	void OnCreateResources();
	void OnReleaseResources();
	
	void AddComponent(BaseComponent* component);
	template<class TYPE> TYPE* GetComponent();

	template <class T>
	T* GetGameState() const;
	void SetGameState(GameState* gameState);

	Vec2 GetPosition() const { return m_transform.GetTranslation();}
	void SetPosition(const Vec2& NewPos) { m_transform.SetTranslation(NewPos);}
	float GetAngle() const { return m_transform.GetRotation(); }
	void SetAngle(float NewAngle) { m_transform.SetRotation(NewAngle); }
	Vec2 GetScale() const { return m_transform.GetScale(); }
	void SetScale(const Vec2& NewScale) { m_transform.SetScale(NewScale); }

	const Transform2D& GetTransform() { return m_transform; }
private:
	vector<BaseComponent*> m_components;
	Transform2D m_transform;
	GameState* m_gameState;
};

template<class TYPE>
TYPE* BaseObject::GetComponent()
{
	for (BaseComponent* component : m_components)
	{
		TYPE* founded = dynamic_cast<TYPE*>(component);
		if (founded)
			return founded;
	}

	return nullptr;
}

template <class T>
T* BaseObject::GetGameState() const
{
	return dynamic_cast<T*>(m_gameState);
}

