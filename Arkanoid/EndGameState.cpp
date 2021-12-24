#include "pch.h"
#include "EndGameState.h"
#include "Game.h"
#include "EndGameLevel.h"
#include "Label.h"

const std::string EndGameState::GameOverLabelId = "GameOverLabel";
const std::string EndGameState::ScoreLabelId = "ScoreLabel";

EndGameState::EndGameState(bool HasWon, Game* GameInstance) : GameState(GameInstance),
bRequestedQuit(false),
bRequestedRestart(false),
bWin(HasWon)
{
	m_level = new EndGameLevel();
}

void EndGameState::Update(float deltaTime)
{
	GameState::Update(deltaTime);

	if (bRequestedQuit)
	{
		game->Quit();
		return;
	}
	
	if (bRequestedRestart)
	{
		UpdateGameState(new PlayState(game));
	}
}

void EndGameState::OnEnter()
{
	GameState::OnEnter();
	std::vector<BaseObject*>& GameObjects = GetGameObjects();

	for (BaseObject* object : GameObjects)
	{
		if (object->GetId() == GameOverLabelId)
		{
			if (Label* label = dynamic_cast<Label*>(object))
			{
				label->SetText(bWin ? L"LEVEL COMPLETED" : L"LEVEL FAILED");
				label->SetForegroundColor(bWin ? DirectX::Colors::Green : DirectX::Colors::Red);
			}
		}
	}
}

void EndGameState::Quit()
{
	bRequestedQuit = true;
}

void EndGameState::Restart()
{
	bRequestedRestart = true;
}
