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
}

void InputHandler::Update(float deltaTime)
{
	/* KEYBOARD HANDLING */
	auto kb = m_keyboard->GetState();
	

	/* MOUSE HANDLING */
	auto mouse = m_mouse->GetState();
	
}

const Vec2 InputHandler::GetMousePosition() const
{
	auto mouse = m_mouse->GetState();
	return Vec2(float(mouse.x), float(mouse.y));
}

bool InputHandler::IsKeyPressed(ArkanoidKeyboardInput input) const
{
	if (input >= ArkanoidKeyboardInput::INPUT_COUNT) return false;
	auto kb = m_keyboard->GetState();

	switch (input)
	{
		case ArkanoidKeyboardInput::ARROW_LEFT:
			return kb.Left;
		case ArkanoidKeyboardInput::ARROW_RIGHT:
			return kb.Right;
		case ArkanoidKeyboardInput::SPACE_BAR:
			return kb.Space;
		case ArkanoidKeyboardInput::ESCAPE:
			return kb.Escape;
		case ArkanoidKeyboardInput::C:
			return kb.C;
	}

	return false;
}

bool InputHandler::IsMouseButtonPressed(ArkanoidMouseInput input) const
{
	if(input >= ArkanoidMouseInput::INPUT_COUNT) return false;
	return false;
}

