#include "pch.h"
#include "PlayState.h"
#include "Level1.h"
#include "BaseObject.h"
#include "TextComponent.h"

PlayState::PlayState(Game* GameInstance) : GameState(GameInstance)
{
	m_level = new Level1();
}

void PlayState::GameOver()
{
	// #Todo manage Game Over
}

void PlayState::OnEnter()
{
	if (m_level)
	{
		m_level->Load(this);
	}
}

void PlayState::OnExit()
{
	Reset();
}
