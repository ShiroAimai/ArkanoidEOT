#pragma once
#include <vector>

class BaseObject;
class CollisionComponent;
class BaseComponent;

struct RendererData;

class GameState
{
public:
	using GameObjects = std::vector<BaseObject*>;
	GameState() = default;
	virtual ~GameState();
	
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Render(const RendererData& Renderer);

	virtual void FixedUpdate();
	virtual void Update(float deltaTime);
	virtual void CreateResources();
	virtual void ReleaseResources();
	virtual void OnWindowSizeUpdate(float xRatio, float yRatio);

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	void Reset();

	bool FindCollisions(const CollisionComponent& RequestorComp, GameObjects* Collisions = nullptr, const GameObjects* Ignores = nullptr) const;

	virtual void AddGameObject(BaseObject* object);
	virtual void RemoveGameObject(BaseObject* object, bool doDelete = true);
protected:
	class BaseLevel* m_level = nullptr;

private:
	using Callback = std::function<void()>;
	using PendingCallbacks = std::vector<Callback>;

	GameObjects m_gameObjects;
	PendingCallbacks m_pendingCallbacks;
};

