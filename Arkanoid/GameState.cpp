#include "pch.h"
#include "GameState.h"
#include "BaseObject.h"
#include <algorithm>

GameState::~GameState()
{
	for (BaseObject* obj : m_gameObjects)
	{
		delete obj;
	}

	m_gameObjects.clear();
}	

void GameState::Render(DirectX::SpriteBatch* batch)
{
	for(BaseObject* Obj : m_gameObjects)
		Obj->Render(batch);
}

void GameState::Update(float deltaTime)
{
	if(m_callbacks.size() > 0)
		ExecutePendingCallbacks();

	for(BaseObject* Obj : m_gameObjects)
		Obj->Update(deltaTime);
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

void GameState::AddCallback(Callback callback)
{
	m_callbacks.push_back(callback);
}

void GameState::AddGameObject(BaseObject* Object)
{
	m_gameObjects.push_back(Object);
	Object->Init();
}

void GameState::RemoveGameObject(BaseObject* Object, bool ShouldDelete /* = true */)
{
	//Is GameObject still in list? Or it was already destroyed by another callback?
	auto cbegin = m_gameObjects.cbegin();
	auto cend = m_gameObjects.cend();

	if (std::find(cbegin, cend, Object) != cend)
	{
		m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), Object), m_gameObjects.end()); //erase alla elements
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

void GameState::ExecutePendingCallbacks()
{
	for (auto& cb : m_callbacks)
		cb();
	
	m_callbacks.clear();
}

