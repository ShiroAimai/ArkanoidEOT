#include "pch.h"
#include "EndGameLevel.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "TextButton.h"
#include "EndGameState.h"
#include "Label.h"

void EndGameLevel::GetLevelObjects(std::vector<BaseObject*>& GameObjects)
{
	std::wstring Fontpath = L"Assets/courier-bold.spritefont";

	std::vector<Sprite*> restartButtonStates;
	restartButtonStates.push_back(Sprite::LoadStatic("idle", L"Assets/button.png",0, 0, 256, 128));
	restartButtonStates.push_back(Sprite::LoadStatic("pressed", L"Assets/button.png", 256, 0, 256, 128));
	int width = restartButtonStates[0]->GetWidth();
	int height = restartButtonStates[0]->GetHeight();
	
	TextButton* restartButton = new TextButton(Fontpath, new VisualComponent(width, height, restartButtonStates));
	restartButton->SetPosition(Vec2(0, -height / 2.f));
	restartButton->SetText(L"PLAY AGAIN");
	restartButton->SetTextScale(Vec2(0.85f, 0.85f));
	restartButton->SetTextEffect(TextEffect::OUTLINE);
	restartButton->SetForegroundColor(DirectX::Colors::Green);
	TextButton& restartButtonRef = *restartButton;
	restartButton->onClick = [&restartButtonRef] { restartButtonRef.GetGameState<EndGameState>()->Restart();};
	GameObjects.push_back(restartButton);

	std::vector<Sprite*> quitButtonStates;
	quitButtonStates.push_back(Sprite::LoadStatic("idle", L"Assets/button.png", 0, 0, 256, 128));
	quitButtonStates.push_back(Sprite::LoadStatic("pressed", L"Assets/button.png", 256, 0, 256, 128));

	TextButton* quitButton = new TextButton(Fontpath, new VisualComponent(width, height, quitButtonStates));
	quitButton->SetPosition(Vec2(0, 128));
	quitButton->SetText(L"QUIT");
	quitButton->SetTextScale(Vec2(0.85f, 0.85f));
	quitButton->SetTextEffect(TextEffect::OUTLINE);
	quitButton->SetForegroundColor(DirectX::Colors::OrangeRed);
	TextButton& quitButtonRef = *quitButton;
	quitButton->onClick = [&quitButtonRef] {
		quitButtonRef.GetGameState<EndGameState>()->Quit();
	};
	GameObjects.push_back(quitButton);

	Label* endGameLabel = new Label(Fontpath);
	endGameLabel->SetPosition(Vec2(0.f, -200.f));
	endGameLabel->SetScale(Vec2(1.4f, 1.4f));
	endGameLabel->SetTextEffect(TextEffect::OUTLINE);
	endGameLabel->SetId(EndGameState::GameOverLabelId);
	GameObjects.push_back(endGameLabel);
}
