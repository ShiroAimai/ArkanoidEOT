#pragma once
#include <vector>
#include <functional>

class BaseObject;
class CollisionComponent;
class BaseComponent;

struct RendererData;

class GameState
{
public:
	using Callback = std::function<void()>;
	using GameObjects = std::vector<BaseObject*>;
	using PendingCallbacks = std::vector<Callback>;

	GameState() = default;
	virtual ~GameState();
	
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Render(const RendererData& Renderer);

	virtual void Update(float deltaTime);
	virtual void OnCreateResources();
	virtual void OnReleaseResources();
	virtual void OnWindowSizeUpdate(float xRatio, float yRatio);

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	void AddCallback(Callback callback);
	void AddGameObject(BaseObject* Object);
	void RemoveGameObject(BaseObject* Object, bool ShouldDelete = true);

	void Reset();

	bool FindCollisions(const CollisionComponent& RequestorComp, GameObjects* Collisions = nullptr, const GameObjects* Ignores = nullptr) const;
private:
	void ExecutePendingCallbacks();

protected:
	class BaseLevel* m_level = nullptr;

private:
	GameObjects m_gameObjects;
	PendingCallbacks m_callbacks;
};

