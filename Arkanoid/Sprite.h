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

	int m_x, m_y;
	std::shared_ptr<Texture> m_texture;
	std::wstring m_path;
	std::string m_id;

	void CreateSprite(const std::wstring& path);
protected:
	Sprite() noexcept;

public:
	static Sprite* LoadStatic(const std::string& id, const std::wstring& path, int u = 0, int v = 0, int width = -1, int height = -1);
	static Sprite* LoadAnimSprite(const std::string& id, const std::wstring& path, int frameCount = 0, int framePerSecond = 0, bool isLooped = false);

	~Sprite();
	Sprite(const Sprite&) = default;
	Sprite& operator= (const Sprite&) = default;

	Sprite(Sprite&&) = default;
	Sprite& operator= (Sprite&&) = default;

	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer, DirectX::XMVECTORF32 color = DirectX::Colors::White);
	void Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, int frame, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer, DirectX::XMVECTORF32 color = DirectX::Colors::White);
	void Update(float deltaTime);
	void Reset();

	void CreateResources();
	void ReleaseResources();

	const std::string GetId() const { return m_id;}

	void Play();
	void Pause();
	void Stop();

	bool IsPlaying() const;
	bool IsLooped() const;
	bool IsAnimated() const;

	int GetWidth() const;
	int GetHeight() const;
};

