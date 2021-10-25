#pragma once
#include "BaseComponent.h"
#include "Vec2.h"
#include <vector>

using std::vector;
class Sprite;
class VisualComponent : public BaseComponent
{
public:
	VisualComponent(int width, int height, Sprite* Sprite);
	VisualComponent(int width, int height, const vector<Sprite*>& sprites);
	virtual ~VisualComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render(DirectX::SpriteBatch* batch) override;

	void SetRenderSpriteIndex(int index);
	const Vec2& GetAnchor()    const { return m_anchor; }
	void SetAnchor(const Vec2& anchor) { m_anchor = anchor; }

	virtual uint8_t GetUpdatePriority() const override{ return 1; }
private:
	Vec2 m_anchor;
	int m_width, m_height;
	vector<Sprite*> m_sprites;
	Sprite* m_currentRenderSprite;
};

