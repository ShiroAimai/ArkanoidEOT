#include "pch.h"
#include "PlayState.h"
#include "Level1.h"

PlayState::PlayState()
{
	m_level = new Level1();
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
