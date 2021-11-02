#pragma once

#include <stdexcept>
#include <SpriteBatch.h>
#include "Vec2.h"

class Texture;

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

	std::shared_ptr<Texture> m_texture;
	std::wstring m_path;

	void CreateSprite(const std::wstring& path);
protected:
	Sprite() noexcept;

public:
	static Sprite* Load(const std::wstring& path, int frameCount = 0, int framePerSecond = 0, bool isLooped = false);

	~Sprite();
	Sprite(const Sprite&) = default;
	Sprite& operator= (const Sprite&) = default;

	Sprite(Sprite&&) = default;
	Sprite& operator= (Sprite&&) = default;

	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer);
	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, int frame, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer);
	void Update(float deltaTime);
	void Reset();

	void OnCreateResources();
	void OnReleaseResources();

	void Play();
	void Pause();
	void Stop();

	bool IsPlaying() const;
	bool IsLooped() const;
	bool IsAnimated() const;

	int GetWidth() const;
	int GetHeight() const;
};

