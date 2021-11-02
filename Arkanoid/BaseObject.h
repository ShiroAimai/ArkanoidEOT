#pragma once
#include <vector>
#include "Transform2D.h"

using std::vector;

class BaseComponent;

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();
	
	BaseObject(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&) = delete;

	virtual void Init();
	virtual void Uninit();
	virtual void Update(float deltaTime);
	virtual void Render(DirectX::SpriteBatch* batch);
	
	void OnCreateResources();
	void OnReleaseResources();
	
	void AddComponent(BaseComponent* component);
	template<class TYPE> TYPE* GetComponent();

	Vec2 GetPosition() const { return m_transform.GetTranslation();}
	void SetPosition(const Vec2& NewPos) { m_transform.SetTranslation(NewPos);}
	float GetAngle() const { return m_transform.GetRotation(); }
	void SetAngle(float NewAngle) { m_transform.SetRotation(NewAngle); }
	Vec2 GetScale() const { return m_transform.GetScale(); }
	void SetScale(const Vec2& NewScale) { m_transform.SetScale(NewScale); }
private:
	vector<BaseComponent*> m_components;
	Transform2D m_transform;
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

