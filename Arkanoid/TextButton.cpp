#include "pch.h"
#include "TextButton.h"
#include "TextComponent.h"

TextButton::TextButton(const std::wstring& FontPath, VisualComponent* VisualButton) : Button(VisualButton)
{
	m_label = new Label(FontPath);
}

void TextButton::SetPosition(const Vec2& NewPos)
{
	Button::SetPosition(NewPos);
	m_label->SetPosition(NewPos + m_label->GetPosition());
}

void TextButton::SetAngle(float NewAngle)
{
	Button::SetAngle(NewAngle);
	m_label->SetAngle(NewAngle + m_label->GetAngle());
}

void TextButton::SetScale(const Vec2& NewScale)
{
	Button::SetScale(NewScale);
	m_label->SetScale(NewScale + m_label->GetScale());
}

void TextButton::Update(float deltaTime)
{
	Button::Update(deltaTime);
	m_label->Update(deltaTime);
}

void TextButton::Render(std::vector<BaseComponent*>& RenderableSprites, std::vector<BaseComponent*>& RenderablePrimitives)
{
	Button::Render(RenderableSprites, RenderablePrimitives);
	m_label->Render(RenderableSprites, RenderablePrimitives);
}

void TextButton::SetForegroundColor(DirectX::XMVECTORF32 Color) { m_label->SetForegroundColor(Color); }
void TextButton::SetBackgroundColor(DirectX::XMVECTORF32 Color) { m_label->SetBackgroundColor(Color); }
void TextButton::SetTextOffset(const Vec2& OffsetPosition) { m_label->SetTextOffset(OffsetPosition); }
void TextButton::SetTextEffect(TextEffect Effect) { m_label->SetTextEffect(Effect); }
void TextButton::SetText(const std::wstring& Text) { m_label->SetText(Text); }

void TextButton::SetTextScale(const Vec2& Scale)
{
	m_label->SetScale(Scale);
}
