#include "pch.h"
#include "TextButton.h"
#include "TextComponent.h"

TextButton::TextButton(VisualComponent* VisualButton) : Button(VisualButton)
{
	m_textComp = new TextComponent(L"Assets/courier.spritefont");
	AddComponent(m_textComp);
}

void TextButton::SetForegroundColor(DirectX::XMVECTORF32 Color) { m_textComp->SetForegroundColor(Color); }
void TextButton::SetBackgroundColor(DirectX::XMVECTORF32 Color) { m_textComp->SetBackgroundColor(Color); }
void TextButton::SetTextOffset(const Vec2& OffsetPosition) { m_textComp->SetOffset(OffsetPosition); }
void TextButton::SetTextEffect(TextEffect Effect) { m_textComp->SetEffect(Effect); }
void TextButton::SetText(const std::wstring& Text) { m_textComp->SetText(Text); }