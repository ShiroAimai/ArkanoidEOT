#include "pch.h"
#include "Label.h"

Label::Label(const std::wstring& FontPath)
{
	m_textComp = new TextComponent(FontPath);
	AddComponent(m_textComp);
}

void Label::SetForegroundColor(DirectX::XMVECTORF32 Color) { m_textComp->SetForegroundColor(Color); }
void Label::SetBackgroundColor(DirectX::XMVECTORF32 Color) { m_textComp->SetBackgroundColor(Color); }
void Label::SetTextOffset(const Vec2& OffsetPosition) { m_textComp->SetOffset(OffsetPosition); }
void Label::SetTextEffect(TextEffect Effect) { m_textComp->SetEffect(Effect); }
void Label::SetText(const std::wstring& Text) { m_textComp->SetText(Text); }
