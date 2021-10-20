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
	virtual void Render(vector<BaseComponent*>& renderables);

	void AddComponent(BaseComponent* component);
	template<class TYPE> TYPE* GetComponent();

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

