#include "pch.h"
#include "PlayerBar.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"

PlayerBar::PlayerBar()
{
	Shape<AABB>* box = new Shape<AABB>;
	box->m_originalShape.m_min = Vec2(-50, -50);
	box->m_originalShape.m_max = Vec2(50, 50);
	CollisionComponent* cc = new CollisionComponent(box);
	AddComponent(cc);

	Sprite* sprite = Sprite::Load(L"Assets/cat.png");
	VisualComponent* vc = new VisualComponent(sprite);
	AddComponent(vc);

}

void PlayerBar::Update(float deltaTime)
{
	Vec2 NewSpeed;
	NewSpeed.x = float(InputHandler::Instance()->IsKeyPressed(ArkanoidKeyboardInput::ARROW_RIGHT) - InputHandler::Instance()->IsKeyPressed(ArkanoidKeyboardInput::ARROW_LEFT));
	NewSpeed.x *= 100; //TODO Replace
	SetSpeed(NewSpeed);
	
	if(CanMove(GetPosition() + NewSpeed * deltaTime))
	{
		MovableObject::Update(deltaTime);
	}
}
