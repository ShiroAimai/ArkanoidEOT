#include "pch.h"
#include "FontManager.h"

FontManager* FontManager::s_instance = nullptr;

FontManager* FontManager::Instance()
{
	if(!s_instance)
		s_instance = new FontManager();
	return s_instance;
}

void FontManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void FontManager::Init(ID3D11Device1* device)
{
	m_device = device;
}

std::shared_ptr<DirectX::SpriteFont> FontManager::Load( const std::wstring& fileName)
{
	if (m_device == nullptr) return nullptr;
		
	const std::wstring key = fileName;
	std::weak_ptr<DirectX::SpriteFont> storedFont = m_mapFonts[key];
	
	if (!storedFont.expired())
		return storedFont.lock();

	std::shared_ptr<DirectX::SpriteFont> font = std::make_shared<DirectX::SpriteFont>(m_device.Get(), fileName.c_str());
	m_mapFonts[key] = std::weak_ptr<DirectX::SpriteFont>(font);

	std::cout << fileName.c_str() << ": Font loaded " << std::endl;

	return font;
}
