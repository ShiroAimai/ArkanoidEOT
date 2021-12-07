#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include "TextureManager.h"

Sprite* Sprite::LoadStatic(const std::string& id, const std::wstring& path, int u /*= 0*/, int v /*= 0*/, int width /*= -1*/, int height /*= -1*/)
{
	Sprite* NewSprite = new Sprite();
	NewSprite->m_id = id;
	NewSprite->m_path = path;
	NewSprite->m_x = u;
	NewSprite->m_y = v;

	NewSprite->m_isLooping = false;
	NewSprite->m_frameCount = 1;
	NewSprite->m_timePerFrame = 0.f;
	NewSprite->m_totalTime = 0.f;

	NewSprite->m_textureWidth = width;
	NewSprite->m_textureHeigth = height;

	NewSprite->CreateSprite(NewSprite->m_path);

	return NewSprite;
}

Sprite* Sprite::LoadAnimSprite(const std::string& id, const std::wstring& path, int frameCount /*= 0*/, int framePerSecond /*= 0*/, bool isLooped /*= false*/)
{
	Sprite* NewSprite = new Sprite();
	NewSprite->m_isLooping = isLooped;
	NewSprite->m_path = path;
	NewSprite->m_id = id;
	if (frameCount && framePerSecond > 0)
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

	NewSprite->CreateSprite(NewSprite->m_path);

	return NewSprite;
}

Sprite::~Sprite()
{
	
}

void Sprite::CreateSprite(const std::wstring& path)
{
	m_texture.reset();
	m_texture = TextureManager::Instance()->Load(path);

	if(m_texture)
	{
		ID3D11ShaderResourceView* internalDirectTexture = m_texture->GetTexture();

		Microsoft::WRL::ComPtr<ID3D11Resource> res;
		internalDirectTexture->GetResource(&res);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
		res.As(&tex2D);

		D3D11_TEXTURE2D_DESC desc;
		tex2D->GetDesc(&desc);

		if(m_textureWidth < 0 && m_textureHeigth < 0)
		{
			m_textureWidth = int(desc.Width);
			m_textureHeigth = int(desc.Height);
		}
	}
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
	m_texture(nullptr),
	m_x(0),
	m_y(0)
{

}

void Sprite::Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer, DirectX::XMVECTORF32 color /* = DirectX::Colors::White*/)
{
	Render(batch, ScreenPosition, m_currentFrame, origin, rotation, scale, RenderLayer, color);
}

void Sprite::Render(DirectX::SpriteBatch* batch, const Vec2& ScreenPosition, int frame, const Vec2& origin, float rotation, const Vec2& scale, float RenderLayer, DirectX::XMVECTORF32 color /* = DirectX::Colors::White*/)
{
	int frameWidth = m_textureWidth / m_frameCount;

	RECT sourceRect;
	sourceRect.left = m_x + frameWidth * frame;
	sourceRect.top = m_y;
	sourceRect.right = sourceRect.left + frameWidth;
	sourceRect.bottom = m_y + m_textureHeigth;

	batch->Draw(m_texture->GetTexture(), ScreenPosition, &sourceRect, color, rotation, origin, scale, DirectX::SpriteEffects_None, RenderLayer);
}

void Sprite::Update(float deltaTime)
{
	if (!IsPlaying()) return;

	m_elapsedTime += deltaTime;
	m_currentFrameTime += deltaTime;

	if (m_currentFrameTime >= m_timePerFrame)
	{
		m_currentFrameTime -= m_timePerFrame;
		if (m_currentFrame < (m_frameCount - 1))
		{
			++m_currentFrame;
		}
		else if (m_currentFrame == (m_frameCount - 1))
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

void Sprite::CreateResources()
{
	CreateSprite(m_path);
}

void Sprite::ReleaseResources()
{
	m_texture.reset();
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

int Sprite::GetWidth() const
{
	return m_textureWidth;
}

int Sprite::GetHeight() const
{
	return m_textureHeigth;
}
