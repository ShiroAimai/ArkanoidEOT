#include "pch.h"
#include "Texture.h"

Texture::Texture(ID3D11ShaderResourceView* texture)
	: m_texture(texture)
{

}

ID3D11ShaderResourceView* Texture::GetTexture() const
{
	return m_texture.Get();
}