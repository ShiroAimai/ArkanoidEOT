#pragma once
#include <vector>

class BaseObject;
class CollisionComponent;
class BaseComponent;

struct RendererData;

class Game;
class GameState
{
public:
	using GameObjects = std::vector<BaseObject*>;
	GameState(Game* GameInstance);
	virtual ~GameState();
	
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Render(const RendererData& Renderer);

	virtual void FixedUpdate();
	virtual void Update(float deltaTime);
	virtual void CreateResources();
	virtual void ReleaseResources();
	virtual void OnWindowSizeUpdate(float xRatio, float yRatio);

	virtual void OnEnter();
	virtual void OnExit();

	void Reset();

	bool FindCollisions(const CollisionComponent& RequestorComp, GameObjects* Collisions = nullptr, const GameObjects* Ignores = nullptr) const;

	virtual void AddGameObject(BaseObject* object);
	virtual void RemoveGameObject(BaseObject* object, bool doDelete = true);

	void UpdateGameState(GameState* NewState);
protected:
	class BaseLevel* m_level = nullptr;

	/* Does not own GameInstace*/
	class Game* game;

	virtual void AddGameObjectImmediate(BaseObject* object);
	std::vector<BaseObject*>& GetGameObjects() { return m_gameObjects; }
private:
	using Callback = std::function<void()>;
	using PendingCallbacks = std::vector<Callback>;

	GameObjects m_gameObjects;
	PendingCallbacks m_pendingCallbacks;
};

