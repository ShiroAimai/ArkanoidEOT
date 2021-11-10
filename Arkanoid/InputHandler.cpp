#include "pch.h"
#include "InputHandler.h"
#include "Vec2.h"

InputHandler::InputHandler() :
	m_keyboard(nullptr), 
	m_mouse(nullptr)
{

}

InputHandler* InputHandler::s_instance = nullptr;

InputHandler* InputHandler::Instance()
{
	if (!s_instance)
	{
		s_instance = new InputHandler();
	}

	return s_instance;
}

void InputHandler::Destroy()
{
	delete s_instance;
}

void InputHandler::Init(HWND Window)
{
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(Window);
}

void InputHandler::Reset()
{
	m_keys.Reset();
	m_mouseButtons.Reset();
}

void InputHandler::Update(float deltaTime)
{
	/* KEYBOARD HANDLING */
	auto kb = m_keyboard->GetState();
	m_keys.Update(kb);

	/* MOUSE HANDLING */
	auto mouse = m_mouse->GetState();
	m_mouseButtons.Update(mouse);
}

const Vec2 InputHandler::GetMousePosition() const
{
	auto mouse = m_mouse->GetState();
	return Vec2(float(mouse.x), float(mouse.y));
}

bool InputHandler::IsKeyDown(ArkanoidKeyboardInput input) const
{
	if (input >= ArkanoidKeyboardInput::INPUT_COUNT) return false;

	switch (input)
	{
	case ArkanoidKeyboardInput::ARROW_LEFT:
		return m_keys.pressed.Left;
	case ArkanoidKeyboardInput::ARROW_RIGHT:
		return m_keys.pressed.Right;
	case ArkanoidKeyboardInput::SPACE_BAR:
		return m_keys.pressed.Space;
	case ArkanoidKeyboardInput::ESCAPE:
		return m_keys.pressed.Escape;
	case ArkanoidKeyboardInput::C:
		return m_keys.pressed.C;
	}

	return false;
}

bool InputHandler::IsKeyPressed(ArkanoidKeyboardInput input) const
{
	if (input >= ArkanoidKeyboardInput::INPUT_COUNT) return false;

	switch (input)
	{
	case ArkanoidKeyboardInput::ARROW_LEFT:
		return m_keys.pressed.Left;
	case ArkanoidKeyboardInput::ARROW_RIGHT:
		return m_keys.pressed.Right;
	case ArkanoidKeyboardInput::SPACE_BAR:
		return m_keys.pressed.Space;
	case ArkanoidKeyboardInput::ESCAPE:
		return m_keys.pressed.Escape;
	case ArkanoidKeyboardInput::C:
		return m_keys.pressed.C;
	}

	return false;
}

bool InputHandler::IsKeyReleased(ArkanoidKeyboardInput input) const
{
	if (input >= ArkanoidKeyboardInput::INPUT_COUNT) return false;

	switch (input)
	{
	case ArkanoidKeyboardInput::ARROW_LEFT:
		return m_keys.released.Left;
	case ArkanoidKeyboardInput::ARROW_RIGHT:
		return m_keys.released.Right;
	case ArkanoidKeyboardInput::SPACE_BAR:
		return m_keys.released.Space;
	case ArkanoidKeyboardInput::ESCAPE:
		return m_keys.released.Escape;
	case ArkanoidKeyboardInput::C:
		return m_keys.released.C;
	}

	return false;
}

bool InputHandler::IsMouseButtonPressed(ArkanoidMouseInput input) const
{
	if(input >= ArkanoidMouseInput::INPUT_COUNT) return false;
	return false;
}

