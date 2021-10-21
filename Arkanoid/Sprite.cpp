#include "pch.h"
#include "Sprite.h"


Sprite* Sprite::Load(ID3D11Device3* device, const wchar_t* path, int frameCount /*= 0*/, int framePerSecond /*= 0*/, bool isLooped /*= false*/)
{
	Sprite* NewSprite = new Sprite();
	NewSprite->CreateSprite(device, path);
	NewSprite->m_isLooping = isLooped;
	if(frameCount && framePerSecond > 0)
	{
		NewSprite->m_frameCount = frameCount;
		NewSprite->m_timePerFrame = 1.f / framePerSecond;
	}
	else
	{
		NewSprite->m_frameCount = 1;
		NewSprite->m_timePerFrame = 0.f;
	}
	NewSprite->m_totalTime = NewSprite->m_frameCount * NewSprite->m_timePerFrame;
	return NewSprite;
}

Sprite::~Sprite()
{
	m_texture.Reset();
}

void Sprite::CreateSprite(ID3D11Device3* device, const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> res;
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			device,
			path,
			res.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()
		));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
	res.As(&tex2D);

	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);

	m_textureWidth = int(desc.Width);
	m_textureHeigth = int(desc.Height);
}

Sprite::Sprite() noexcept
	: m_isPlaying(false),
	m_isLooping(false),
	m_currentFrame(0),
	m_frameCount(0),
	m_timePerFrame(0.f),
	m_currentFrameTime(0.f),
	m_totalTime(0.f),
	m_elapsedTime(0.f),
	m_texture(nullptr)
{

}

void Sprite::Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, const Vec2& origin, float rotation, const Vec2& scale)
{
	Render(batch, ScreenPosition, m_currentFrame, origin, rotation, scale);
}

void Sprite::Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, int frame, const Vec2& origin, float rotation, const Vec2& scale)
{
	int frameWidth = m_textureWidth / m_frameCount;

	RECT sourceRect;
	sourceRect.left = frameWidth * frame;
	sourceRect.top = 0;
	sourceRect.right = sourceRect.left + frameWidth;
	sourceRect.bottom = m_textureHeigth;
	
	batch->Draw(m_texture.Get(), ScreenPosition, &sourceRect , DirectX::Colors::White, (rotation / DirectX::XM_PI) * 180, origin, scale, DirectX::SpriteEffects_None, 0.f);
}

void Sprite::Update(float deltaTime)
{
	if(!IsPlaying()) return;

	m_elapsedTime += deltaTime;
	m_currentFrameTime += deltaTime;

	if (m_currentFrameTime >= m_timePerFrame)
	{		
		m_currentFrameTime -= m_timePerFrame;
		if (m_currentFrame < (m_frameCount - 1))
		{
			++m_currentFrame;
		}
		else if(m_currentFrame == (m_frameCount - 1))
		{
			if (IsLooped())
			{
				m_currentFrame = 0;
			}
			else
			{
				m_isPlaying = false;
				m_elapsedTime = m_totalTime;
			}
		}
	}
}

void Sprite::Reset()
{
	m_currentFrame = 0;
	m_elapsedTime = 0.f;
}

void Sprite::Play()
{
	if (!IsAnimated()) return; //no animated sprite
	if (!IsPlaying())
	{
		m_isPlaying = true;
		m_currentFrame = 0;
		m_elapsedTime = 0.f;
	}
}

void Sprite::Pause()
{
	if (!IsAnimated()) return; //no animated sprite
	m_isPlaying = false;
}

void Sprite::Stop()
{
	if (!IsAnimated()) return; //no animated sprite
	m_isPlaying = false;
	m_currentFrame = 0;
	m_elapsedTime = m_currentFrameTime * m_timePerFrame;
	m_currentFrameTime = 0.f;
}

bool Sprite::IsPlaying() const
{
	return m_isPlaying;
}

bool Sprite::IsLooped() const
{
	return m_isLooping;
}

bool Sprite::IsAnimated() const
{
	return m_frameCount > 1; 
}
