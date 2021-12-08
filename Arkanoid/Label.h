#pragma once
#include "BaseObject.h"
#include "TextComponent.h"

class Label : public BaseObject
{
public:
	Label();

	void SetForegroundColor(DirectX::XMVECTORF32 Color);
	void SetBackgroundColor(DirectX::XMVECTORF32 Color);
	void SetTextOffset(const Vec2& OffsetPosition);
	void SetTextEffect(TextEffect Effect);
	void SetText(const std::wstring& Text);
private: 
	TextComponent* m_textComp;
};

