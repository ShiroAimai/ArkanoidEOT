#include "pch.h"
#include "RendererData.h"

RendererData::RendererData(DirectX::SpriteBatch* SpriteBatch, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* PrimitiveBatch)
: m_spriteBatch(SpriteBatch), m_primitiveBatch(PrimitiveBatch)
{

}
