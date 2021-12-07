#include "pch.h"
#include "Button.h"
#include "Collision.h"
#include "CollisionComponent.h"
#include "InputHandler.h"
#include "VisualComponent.h"
#include "Sprite.h"
#include "WorldHelper.h"

Button::Button(VisualComponent* ButtonVisual)
{
	assert(ButtonVisual != nullptr);
	AddComponent(ButtonVisual);
	m_visualComp = ButtonVisual;
}

void Button::Update(float deltaTime)
{
	BaseObject::Update(deltaTime);
	
	if(!m_visualComp) return;

	PrevState = CurrentState;

	Vec2 MousePos = InputHandler::Instance()->GetMousePosition();
	bool IsMouseOverButton = TestHit(MousePos);

	m_visualComp->SetRenderSpriteByIndex(IsMouseOverButton);
	
	if (IsMouseOverButton && InputHandler::Instance()->IsMouseButtonPressed(ArkanoidMouseInput::LEFT))
	{
		CurrentState = ButtonState::Pressed;
		if(onClick)
		{
			onClick();
		}
	}
	else
	{
		CurrentState = ButtonState::Idle;
	}
}

bool Button::TestHit(const Vec2& MousePos)
{
	if (m_visualComp)
	{
		//subtract world matrix translation
		const Matrix& WorldMatrix = WorldHelper::Instance()->GetWorldMatrix();
		Vec2 CorrecteMousePos = MousePos;
		CorrecteMousePos.x -= WorldMatrix._41;
		CorrecteMousePos.y -= WorldMatrix._42;


		Vec2 anchorOffset(m_visualComp->GetWidth() * m_visualComp->GetAnchor().x, m_visualComp->GetHeight() * m_visualComp->GetAnchor().y);

		Vec2 parentPosition = GetPosition();

		return (CorrecteMousePos.x <= parentPosition.x + anchorOffset.x &&
			CorrecteMousePos.x >= parentPosition.x - anchorOffset.x&&
			CorrecteMousePos.y <= parentPosition.y + anchorOffset.y &&
			CorrecteMousePos.y >= parentPosition.y - anchorOffset.y);
	}

	return false;
}
