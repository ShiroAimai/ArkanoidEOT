#include "pch.h"
#include "WorldHelper.h"

WorldHelper::WorldHelper() :
 m_gameBounds(),
 m_world(Matrix::Identity)
{

}

WorldHelper* WorldHelper::s_instance = nullptr;

WorldHelper* WorldHelper::Instance()
{
	if (!s_instance)
	{
		s_instance = new WorldHelper;
	}

	return s_instance;
}

void WorldHelper::Destroy()
{
	delete s_instance;
}

const RECT& WorldHelper::GetGameBounds() const
{
	return m_gameBounds;
}

void WorldHelper::SetGameBounds(const RECT& bounds)
{
	m_gameBounds = bounds;
}

const Matrix& WorldHelper::GetWorldMatrix() const
{
	return m_world;
}

void WorldHelper::SetWorldMatrix(const Matrix& matrix)
{
	m_world = matrix;
}


