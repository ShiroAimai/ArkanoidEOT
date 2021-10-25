#pragma once
#include "BaseObject.h"

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();
	BaseComponent(const BaseComponent&) = default;
	BaseComponent& operator=(const BaseComponent&) = default;

	void SetParent(BaseObject* NewParent);

	//Base Lifecycle
	virtual void Init();
	virtual void Uninit();
	virtual void Render(DirectX::SpriteBatch* batch);
	virtual void Update(float deltaTime);

	virtual uint8_t GetUpdatePriority() const = 0;
	//Contained in interval [0, 1]
	virtual float GetRenderLayer() const { return m_renderLayer; } // Not rendered by default
	void SetRenderLayer(uint8_t Layer);
protected:
	BaseObject* m_parent;

private:
	float m_renderLayer;
};

