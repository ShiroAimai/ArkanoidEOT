#pragma once
#include "BaseObject.h"
#include <functional>

class VisualComponent;

class Button : public BaseObject
{
public:
	Button(VisualComponent* ButtonVisual);
	virtual void Update(float deltaTime) override;

	bool IsPressed() const { return CurrentState == ButtonState::Pressed;}
	bool IsReleased() const { return PrevState == ButtonState::Pressed && CurrentState == ButtonState::Idle; }

	std::function<void()> onClick = nullptr;
private:
	bool TestHit(const Vec2& MousePos);

	enum class ButtonState
	{
		Idle = 0,
		Pressed
	};

	ButtonState CurrentState = ButtonState::Idle;
	ButtonState PrevState = ButtonState::Idle;
	VisualComponent* m_visualComp = nullptr;
};

