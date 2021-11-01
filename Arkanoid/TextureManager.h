#pragma once
#include <map>

class Texture;
class TextureManager
{
public:
	static TextureManager* Instance();
	static void Destroy();

	void Init(ID3D11Device1* device);
	std::shared_ptr<Texture> Load(const std::wstring& fileName);
private:
	TextureManager() = default;

	using Textures = std::map<std::wstring, std::weak_ptr<Texture>>;
	Textures m_textureMap;
	
	Microsoft::WRL::ComPtr<ID3D11Device1> m_device;
	static TextureManager* s_instance;
};

