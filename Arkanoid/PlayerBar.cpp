#include "pch.h"
#include "PlayerBar.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"

PlayerBar::PlayerBar()
{
	Sprite* sprite = Sprite::Load(L"Assets/player_bar.png");
	VisualComponent* vc = new VisualComponent(sprite);
	AddComponent(vc);

	Shape<AABB>* box = new Shape<AABB>;
	box->m_originalShape.m_min = Vec2(-70, -16);
	box->m_originalShape.m_max = Vec2(70, 16);
	CollisionComponent* cc = new CollisionComponent(box);
	cc->SetShapeColor(DirectX::Colors::Yellow);
	AddComponent(cc);

	SetSpeed(160.f);
}

void PlayerBar::Update(float deltaTime)
{
	Vec2 NewVelocity;
	NewVelocity.x = float(InputHandler::Instance()->IsKeyDown(ArkanoidKeyboardInput::ARROW_RIGHT) - InputHandler::Instance()->IsKeyDown(ArkanoidKeyboardInput::ARROW_LEFT));
	SetVelocity(NewVelocity);
	
	if(CanMove(GetPosition() + NewVelocity * deltaTime * GetSpeed()))
	{
		MovableObject::Update(deltaTime);
	}
}
