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

	virtual void OnCreateResources() = 0;
	virtual void OnReleaseResources() = 0;

	//Contained in interval [0, 1]
	float GetRenderLayer() const { return m_renderLayer; } // Not rendered by default
	void SetRenderLayer(uint8_t Layer);

	uint8_t GetUpdatePriority() const { return m_updatePriority; }
	void SetUpdatePriority(uint8_t Priority);

protected:
	BaseObject* m_parent;

private:
	float m_renderLayer;
	uint8_t m_updatePriority;
};

