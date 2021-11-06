#pragma once

struct RendererData
{
	RendererData(DirectX::SpriteBatch* SpriteBatch, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* PrimitiveBatch);

	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* m_primitiveBatch;
};

