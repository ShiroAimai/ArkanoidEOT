#include "pch.h"
#include "GameState.h"
#include "BaseObject.h"
#include <algorithm>
#include "CollisionComponent.h"
#include "RendererData.h"
#include "InputHandler.h"
#include "WorldHelper.h"

GameState::~GameState()
{
	for (BaseObject* obj : m_gameObjects)
	{
		delete obj;
	}

	m_gameObjects.clear();
}	

void GameState::Render(const RendererData& Renderer)
{
	std::vector<BaseComponent*> renderableSprites, renderablePrimitives;
	for(BaseObject* Obj : m_gameObjects)
		Obj->Render(renderableSprites, renderablePrimitives);

	Renderer.m_primitiveBatch->Begin();

	for (BaseComponent* comp : renderablePrimitives)
		comp->Render(Renderer);

	Renderer.m_primitiveBatch->End();

	Renderer.m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
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

void GameState::Update(float deltaTime)
{
	if(m_callbacks.size() > 0)
		ExecutePendingCallbacks();

	for(BaseObject* Obj : m_gameObjects)
		Obj->Update(deltaTime);

	if(InputHandler::Instance()->IsKeyPressed(ArkanoidKeyboardInput::C))
		CollisionComponent::ShouldRenderCollision = !CollisionComponent::ShouldRenderCollision;
}

void GameState::OnCreateResources()
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->OnCreateResources();
}

void GameState::OnReleaseResources()
{
	for(BaseObject* Obj : m_gameObjects)
		Obj->OnReleaseResources();
}

void GameState::OnWindowSizeUpdate(float xRatio, float yRatio)
{
	for (BaseObject* Obj : m_gameObjects)
		Obj->OnWindowSizeUpdate(xRatio, yRatio);
}

void GameState::AddCallback(Callback callback)
{
	m_callbacks.push_back(callback);
}

void GameState::AddGameObject(BaseObject* Object)
{
	m_gameObjects.push_back(Object);
	Object->Init(this);
}

void GameState::RemoveGameObject(BaseObject* Object, bool ShouldDelete /* = true */)
{
	//Is GameObject still in list? Or it was already destroyed by another callback?
	auto cbegin = m_gameObjects.cbegin();
	auto cend = m_gameObjects.cend();

	if (std::find(cbegin, cend, Object) != cend)
	{
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), Object), m_gameObjects.end()); //erase all elements
		Object->Uninit();

		if (ShouldDelete)
			delete Object;
	}
}

void GameState::Reset()
{
	m_callbacks.clear();
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

	for (BaseObject* Obj : m_gameObjects)
	{
		CollisionComponent* collisionComp = Obj->GetComponent<CollisionComponent>();
		if(!collisionComp) //object should never collide 
			continue;
		//Current Obj was added to list of objects to not consider during collision handling
		if(ignores && std::find(ignores->begin(), ignores->end(), Obj) != ignores->end())
			continue;
		//no collision found between objects
		if (!collisionComp->Intersect(RequestorComp))
			continue;
		collisions->push_back(Obj);
	}

	return collisions && collisions->size() > 0;
}

void GameState::ExecutePendingCallbacks()
{
	for (auto& cb : m_callbacks)
		cb();
	
	m_callbacks.clear();
}

