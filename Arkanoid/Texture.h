#pragma once

class Texture
{
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

public:
	Texture(ID3D11ShaderResourceView* texture);
	ID3D11ShaderResourceView* GetTexture() const;
};

