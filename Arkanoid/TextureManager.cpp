#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::s_instance = nullptr;

TextureManager* TextureManager::Instance()
{
	if (!s_instance)
	{
		s_instance = new TextureManager();
	}
	return s_instance;
}

void TextureManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void TextureManager::Init(ID3D11Device1* device)
{
	m_device = device;
}

std::shared_ptr<Texture> TextureManager::Load(const std::wstring& fileName)
{
	if (m_textureMap[fileName].expired())
	{
		ID3D11ShaderResourceView* texture = nullptr;

		HRESULT res = DirectX::CreateWICTextureFromFile(			
			m_device.Get(),
			fileName.c_str(),
			nullptr,
			&texture
			);
		
		if (SUCCEEDED(res))
		{
			std::cout << fileName.c_str() << ": Texture loaded " << std::endl;
			std::shared_ptr<Texture> shared_texture = std::make_shared<Texture>(texture);
			m_textureMap[fileName] = std::weak_ptr<Texture>(shared_texture);
			return shared_texture;
		}

		return nullptr;
	}

	return m_textureMap[fileName].lock();
}
