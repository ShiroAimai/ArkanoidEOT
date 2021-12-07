#include "pch.h"
#include "TextComponent.h"
#include "FontManager.h"

TextComponent::TextComponent(const std::wstring& Text, const std::wstring& Font)
	: m_text(Text), m_fontName(Font), m_foreground(DirectX::Colors::Black), m_background(DirectX::Colors::Black)
{
	SetRenderLayer(1);
	if (!m_font)
	{
		CreateResources();
	}
}

TextComponent::TextComponent(const std::wstring& Text, const std::wstring& Font, const Vec2& Offset)
: m_text(Text), m_fontName(Font), m_textOffset(Offset), m_foreground(DirectX::Colors::Black), m_background(DirectX::Colors::Black)
{
	SetRenderLayer(1);
	if (!m_font)
	{
		CreateResources();
	}
}

void TextComponent::Render(const RendererData& Renderer)
{
	Vec2 Pos = m_parent->GetPosition();

	Vec2 origin = m_font->MeasureString(m_text.c_str());
	origin /= 2.f;
	origin += m_textOffset;

	float angleInRad = m_parent->GetAngle() * DirectX::XM_PI / 180.f;

	Vec2 Scale = m_parent->GetScale();
	
	if (m_effect == TextEffect::SHADOWS)
	{
		DrawShadows(Renderer.m_spriteBatch, m_text, Pos, origin, Scale, angleInRad);
	}
	else if (m_effect == TextEffect::OUTLINE)
	{
		DrawOutline(Renderer.m_spriteBatch, m_text, Pos, origin, Scale, angleInRad);
	}

	m_font->DrawString(Renderer.m_spriteBatch, m_text.c_str(), Pos, m_foreground, angleInRad, origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
}

void TextComponent::CreateResources()
{
	m_font.reset();
	m_font = FontManager::Instance()->Load(m_fontName);
}

void TextComponent::ReleaseResources()
{
	m_font.reset();
}

void TextComponent::SetForegroundColor(DirectX::XMVECTORF32 Color)
{
	m_foreground = Color;
}

void TextComponent::SetBackgroundColor(DirectX::XMVECTORF32 Color)
{
	m_background = Color;
}

void TextComponent::SetOffset(Vec2 OffsetPosition)
{
	m_textOffset = OffsetPosition;
}

void TextComponent::SetEffect(TextEffect Effect)
{
	m_effect = Effect;
}

void TextComponent::SetText(const std::wstring& Text)
{
	m_text = Text;
}

void TextComponent::DrawShadows(DirectX::SpriteBatch* Batch, const std::wstring& Text, const Vec2& ScreenPos, const Vec2& Origin, const Vec2& Scale, float rotation)
{
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(1.f, 1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(-1.f, 1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
}

void TextComponent::DrawOutline(DirectX::SpriteBatch* Batch, const std::wstring& Text, const Vec2& ScreenPos, const Vec2& Origin, const Vec2& Scale, float rotation)
{
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(1.f, 1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(-1.f, 1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(-1.f, -1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
	m_font->DrawString(Batch, Text.c_str(),
		ScreenPos + Vec2(1.f, -1.f), m_background, rotation, Origin, Scale, DirectX::SpriteEffects::SpriteEffects_None, GetRenderLayer());
}
