#pragma once
#include "BaseObject.h"
#include "RendererData.h"

enum class RenderMode
{
	Sprite,
	Primitive
};

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
	virtual void Render(const RendererData& Renderer);
	virtual void Update(float deltaTime);

	virtual void OnCreateResources() {};
	virtual void OnReleaseResources() {};

	RenderMode GetRenderMode() const { return m_renderMode; }
	//Contained in interval [0, 1]
	float GetRenderLayer() const { return m_renderLayer; } // Not rendered by default
	void SetRenderLayer(uint8_t Layer);

	uint8_t GetUpdatePriority() const { return m_updatePriority; }
	void SetUpdatePriority(uint8_t Priority);
	
protected:
	BaseObject* m_parent;
	RenderMode m_renderMode;
private:
	float m_renderLayer;
	uint8_t m_updatePriority;
};

