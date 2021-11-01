#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>
#include <DirectXMath.h>

enum class TextEffect
{
	NONE,
	SHADOWS,
	OUTLINE
};

class TextComponent : public BaseComponent
{
private:
	std::shared_ptr<DirectX::SpriteFont> m_font;
	DirectX::XMVECTORF32 m_foreground, m_background;
	std::wstring m_text;
	Vec2 m_textOffset;
	TextEffect m_effect;
	
	void DrawShadows(DirectX::SpriteBatch* Batch, const std::wstring& Text, const Vec2& ScreenPos, const Vec2& Origin, const Vec2& Scale, float rotation);
	void DrawOutline(DirectX::SpriteBatch* Batch, const std::wstring& Text, const Vec2& ScreenPos, const Vec2& Origin, const Vec2& Scale, float rotation);

	void Init(const std::wstring& Font);
public:
	TextComponent(const std::wstring& Text, const std::wstring& Font);
	TextComponent(const std::wstring& Text, const std::wstring& Font, const Vec2& Offset);

	virtual void Render(DirectX::SpriteBatch* batch) override;

	virtual uint8_t GetUpdatePriority() const override { return 1; }

	void SetForegroundColor(DirectX::XMVECTORF32 Color);
	void SetBackgroundColor(DirectX::XMVECTORF32 Color);
	void SetOffset(Vec2 OffsetPosition);
	void SetEffect(TextEffect Effect);
	void SetText(const std::wstring& Text);
};

