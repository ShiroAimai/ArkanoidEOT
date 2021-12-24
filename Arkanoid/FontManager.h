#pragma once
#include <map>

class FontManager
{
public:
	static FontManager* Instance();
	static void Destroy();

	void Init(ID3D11Device1* device);
	std::shared_ptr<DirectX::SpriteFont> Load(const std::wstring& fileName);

private:
	FontManager() = default;
	
	using Fonts = std::map<std::wstring, std::weak_ptr<DirectX::SpriteFont>>;
	Fonts m_mapFonts;
	Microsoft::WRL::ComPtr<ID3D11Device1> m_device;
	static FontManager* s_instance;
};

