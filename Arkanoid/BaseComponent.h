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
	virtual uint8_t GetRenderLayer() const { return 0; } // Not rendered by default

protected:
	BaseObject* m_parent;
};

