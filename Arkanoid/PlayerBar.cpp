#include "pch.h"
#include "PlayerBar.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "VisualComponent.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "Ball.h"

PlayerBar::PlayerBar() : m_storedBall(nullptr), m_storedBallAttachOffset(Vec2::Zero)
{
	Sprite* sprite = Sprite::Load(L"Assets/player_bar.png");
	m_visualComp = new VisualComponent(sprite);
	AddComponent(m_visualComp);

	Shape<AABB>* box = new Shape<AABB>;
	box->m_originalShape.m_min = Vec2(-70, -16);
	box->m_originalShape.m_max = Vec2(70, 16);
	m_collisionComp = new CollisionComponent(box);
	m_collisionComp->SetShapeColor(DirectX::Colors::Yellow);
	AddComponent(m_collisionComp);

	SetSpeed(160.f);
}

void PlayerBar::Update(float deltaTime)
{
	Vec2 NewVelocity;
	NewVelocity.x = float(InputHandler::Instance()->IsKeyDown(ArkanoidKeyboardInput::ARROW_RIGHT) - InputHandler::Instance()->IsKeyDown(ArkanoidKeyboardInput::ARROW_LEFT));
	SetVelocity(NewVelocity);

	MovableObject::Update(deltaTime);

	bool ShouldLaunchBall = InputHandler::Instance()->IsKeyPressed(ArkanoidKeyboardInput::SPACE_BAR);
	if (m_storedBall && ShouldLaunchBall)
	{
		LaunchBall();
	}

	//update stored ball if any
	if (m_storedBall)
	{
		m_storedBall->SetPosition(GetPosition() + m_storedBallAttachOffset);
	}
}

bool PlayerBar::StoreBall(Ball* ball)
{
	if (ball && !m_storedBall)
	{
		m_storedBall = ball;
		m_storedBall->SetVelocity(Vec2());

		Shape<AABB>* box = dynamic_cast<Shape<AABB>*>(m_collisionComp->GetShape());
		if (box)
		{
			//negate it to be sure it will be on top of the player bar, add the last +1 to ensure we do not collide
			m_storedBallAttachOffset.y = -1.f * ((box->m_originalShape.m_max.y - box->m_originalShape.m_min.y) / 2.f + m_storedBall->GetRadius() + 1);
		}
		return true;
	}

	return false;
}

bool PlayerBar::LaunchBall()
{
	if (m_storedBall)
	{
		m_storedBall->SetVelocity(GetVelocity() + Vec2(0, -0.5f));
		m_storedBall = nullptr;
		return true;
	}

	return false;
}
