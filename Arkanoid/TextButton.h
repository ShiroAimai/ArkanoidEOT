#pragma once
#include "Button.h"
#include "Label.h"


class TextButton : public Button
{
public:
	TextButton(VisualComponent* VisualButton);

	virtual void SetPosition(const Vec2& NewPos) override;
	virtual void SetAngle(float NewAngle) override;
	virtual void SetScale(const Vec2& NewScale) override;

	virtual void Update(float deltaTime) override;
	virtual void Render(std::vector<BaseComponent *>& RenderableSprites, std::vector<BaseComponent *>& RenderablePrimitives) override;

	void SetForegroundColor(DirectX::XMVECTORF32 Color);
	void SetBackgroundColor(DirectX::XMVECTORF32 Color);
	void SetTextOffset(const Vec2& OffsetPosition);
	void SetTextEffect(TextEffect Effect);
	void SetText(const std::wstring& Text);
	void SetTextScale(const Vec2& Scale);
private:
	Label* m_label;
};

