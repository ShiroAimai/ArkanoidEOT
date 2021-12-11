#include "pch.h"
#include "GameState.h"
#include "BaseObject.h"
#include <algorithm>
#include "CollisionComponent.h"
#include "RendererData.h"
#include "InputHandler.h"
#include "WorldHelper.h"
#include <memory>
#include "Game.h"
#include "BaseLevel.h"

GameState::GameState(Game* GameInstance)
{
	game = GameInstance;
}

GameState::~GameState()
{
	for (BaseObject* obj : m_gameObjects)
	{
		delete obj;
	}

	m_gameObjects.clear();
	
	if (m_level)
	{
		delete m_level;
	}
}

void GameState::Render(const RendererData& Renderer)
{
	std::vector<BaseComponent*> renderableSprites, renderablePrimitives;
	for (BaseObject* Obj : m_gameObjects)
		Obj->Render(renderableSprites, renderablePrimitives);

	Renderer.m_primitiveBatch->Begin();

	for (BaseComponent* comp : renderablePrimitives)
		comp->Render(Renderer);

	Renderer.m_primitiveBatch->End();

	Renderer.m_spriteBatch->Begin(
		DirectX::SpriteSortMode_FrontToBack,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		WorldHelper::Instance()->GetWorldMatrix()
	);

	for (BaseComponent* comp : renderableSprites)
		comp->Render(Renderer);

	Renderer.m_spriteBatch->End();
}

void GameState::FixedUpdate()
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->FixedUpdate();
}

void GameState::Update(float deltaTime)
{
	for (auto cb : m_pendingCallbacks)
	{
		cb();
	}
	m_pendingCallbacks.clear();

	for (BaseObject* Obj : m_gameObjects)
		Obj->Update(deltaTime);

	if (InputHandler::Instance()->IsKeyPressed(ArkanoidKeyboardInput::C))
		CollisionComponent::ShouldRenderCollision = !CollisionComponent::ShouldRenderCollision;
}

void GameState::CreateResources()
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->CreateResources();
}

void GameState::ReleaseResources()
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->ReleaseResources();
}

void GameState::OnWindowSizeUpdate(float xRatio, float yRatio)
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->OnWindowSizeUpdate(xRatio, yRatio);
}


void GameState::OnEnter()
{
	if (m_level)
	{
		std::vector<BaseObject*> LevelObjects;
		m_level->Load(LevelObjects);

		for(BaseObject* obj : LevelObjects)
			AddGameObjectImmediate(obj);
	}
}

void GameState::OnExit()
{
	Reset();
}

void GameState::Reset()
{
	for (int i = 0; i < int(m_gameObjects.size()); i++)
	{
		BaseObject* gameObject = m_gameObjects[i];
		gameObject->Uninit();
		delete gameObject;
	}

	m_gameObjects.clear();
}

bool GameState::FindCollisions(const CollisionComponent& RequestorComp, GameObjects* collisions /*= nullptr*/, const GameObjects* ignores /*= nullptr*/) const
{
	if (collisions)
	{
		collisions->clear();
	}

	if (!RequestorComp.enabled)
		return false;

	for (BaseObject* Obj : m_gameObjects)
	{
		CollisionComponent* collisionComp = Obj->GetComponent<CollisionComponent>();
		if (!collisionComp || !collisionComp->enabled) //object should never collide 
			continue;
		//Current Obj was added to list of objects to not consider during collision handling
		if (ignores && std::find(ignores->begin(), ignores->end(), Obj) != ignores->end())
			continue;
		//no collision found between objects
		if (!collisionComp->Intersect(RequestorComp))
			continue;
		collisions->push_back(Obj);
	}

	return collisions && collisions->size() > 0;
}

void GameState::AddGameObject(BaseObject* object)
{
	m_pendingCallbacks.push_back([=] {
		m_gameObjects.push_back(object);
		object->Init(this);
	});
}

void GameState::AddGameObjectImmediate(BaseObject* object)
{
	m_gameObjects.push_back(object);
	object->Init(this);
}

void GameState::RemoveGameObject(BaseObject* object, bool doDelete /*= true*/)
{
	m_pendingCallbacks.push_back([=] {
		//it's still there?
		if (std::find(m_gameObjects.begin(), m_gameObjects.end(), object) != m_gameObjects.end()) {
			m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), object), m_gameObjects.end());
			object->Uninit();
			if (doDelete) {
				delete object;
			}
		}
	});
}

void GameState::UpdateGameState(GameState* NewState)
{
	game->UpdateGameState(NewState);
}

DirectX::XMVECTORF32 GameState::GetLevelBackground() const
{
	return m_level->GetLevelBackground();
}
