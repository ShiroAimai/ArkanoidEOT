#pragma once

class BaseObject;
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
	virtual void Render();
	virtual void Update(float deltaTime);

	virtual uint8_t getUpdatePriority() const = 0;
	virtual uint8_t getRenderLayer() const { return 0; } // Not rendered by default

private:
	BaseObject* m_parent;
};

