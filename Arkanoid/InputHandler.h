#pragma once

enum class ArkanoidKeyboardInput
{
	ARROW_LEFT = 0,
	ARROW_RIGHT = 1,
	ARROW_DOWN = 2,
	ARROW_UP = 3,
	SPACE_BAR = 4,
	ESCAPE = 5,
	C = 6,
	INPUT_COUNT = 7
};

enum class ArkanoidMouseInput
{
	LEFT = 0,
	RIGHT = 1,
	INPUT_COUNT = 2
};

struct Vec2;

class InputHandler
{
public:
	InputHandler(const InputHandler&) = delete;
	InputHandler(InputHandler&&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;
	InputHandler& operator=(InputHandler&&) = delete;

	static InputHandler* Instance();
	static void Destroy();

	//Handler lifecycle
	void Init(HWND Window);
	void Reset();
	void Update(float deltaTime);

	//Handler API
	
	/* Mouse*/
	const Vec2 GetMousePosition() const;
	bool IsMouseButtonPressed(ArkanoidMouseInput input) const;

	/* Keyboard*/
	bool IsKeyDown(ArkanoidKeyboardInput input) const;
	bool IsKeyPressed(ArkanoidKeyboardInput input) const;
	bool IsKeyReleased(ArkanoidKeyboardInput input) const;

private:
	InputHandler();
	~InputHandler() = default;

private:
	static InputHandler* s_instance;
	
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	DirectX::Keyboard::KeyboardStateTracker m_keys;
	DirectX::Mouse::ButtonStateTracker m_mouseButtons;
};

