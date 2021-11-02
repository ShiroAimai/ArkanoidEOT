#pragma once
#include <vector>
#include <functional>

class BaseObject;

class GameState
{
public:
	using Callback = std::function<void()>;

	GameState() = default;
	virtual ~GameState();
	
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Render(DirectX::SpriteBatch* batch);
	virtual void Update(float deltaTime);
	virtual void OnCreateResources();
	virtual void OnReleaseResources();

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	void AddCallback(Callback callback);
	void AddGameObject(BaseObject* Object);
	void RemoveGameObject(BaseObject* Object, bool ShouldDelete = true);

	void Reset();
private:
	void ExecutePendingCallbacks();

protected:
	class BaseLevel* m_level = nullptr;

private:

	using GameObjects = std::vector<BaseObject*>;
	GameObjects m_gameObjects;
	
	using PendingCallbacks = std::vector<Callback>;
	PendingCallbacks m_callbacks;
};

