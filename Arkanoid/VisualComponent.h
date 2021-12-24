#pragma once
#include "BaseComponent.h"
#include "Vec2.h"
#include <vector>

using std::vector;
class Sprite;

class VisualComponent : public BaseComponent
{
public:
	VisualComponent(Sprite* Sprite);
	VisualComponent(int width, int height, const vector<Sprite*>& sprites);
	virtual ~VisualComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render(const RendererData& Renderer) override;

	virtual void CreateResources() override;
	virtual void ReleaseResources() override;

	void SetRenderSpriteByIndex(int index);
	void SetRenderSpriteById(const std::string& Id);
	
	const Vec2& GetAnchor()    const { return m_anchor; }
	void SetAnchor(const Vec2& anchor) { m_anchor = anchor; }

	DirectX::XMVECTORF32 GetColor() const { return m_color; }
	void SetColor(DirectX::XMVECTORF32 color) { m_color = color; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	
private:
	DirectX::XMVECTORF32 m_color;
	Vec2 m_anchor;
	int m_width, m_height;
	vector<Sprite*> m_sprites;
	Sprite* m_currentRenderSprite;
};

