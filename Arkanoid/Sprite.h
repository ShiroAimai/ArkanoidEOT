#pragma once

#include <stdexcept>
#include <SpriteBatch.h>
#include "Vec2.h"
#include <wrl/client.h>

class Sprite
{
private:
	int m_currentFrame;
	float m_currentFrameTime;
	float m_timePerFrame;
	int m_frameCount;

	float m_totalTime;
	float m_elapsedTime;
	
	bool m_isPlaying;
	bool m_isLooping;
	
	int m_textureWidth;
	int m_textureHeigth;
	Vec2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	void CreateSprite(ID3D11Device3* device, const wchar_t* path);
protected:
	Sprite() noexcept;

public:
	static Sprite* Load(ID3D11Device3* device, const wchar_t* path, const Vec2& origin, int frameCount = 0, int framePerSecond = 0, bool isLooped = false);

	~Sprite();
	Sprite(const Sprite&) = default;
	Sprite& operator= (const Sprite&) = default;

	Sprite(Sprite&&) = default;
	Sprite& operator= (Sprite&&) = default;

	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition);
	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, int frame);
	void Update(float deltaTime);
	void Reset();

	void Play();
	void Pause();
	void Stop();

	bool IsPlaying() const;
	bool IsLooped() const;
	bool IsAnimated() const;
};

