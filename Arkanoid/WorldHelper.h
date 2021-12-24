#pragma once

using DirectX::SimpleMath::Matrix;
class WorldHelper
{
public:
	WorldHelper(const WorldHelper&) = delete;
	WorldHelper(WorldHelper&&) = delete;
	WorldHelper& operator=(const WorldHelper&) = delete;
	WorldHelper& operator=(WorldHelper&&) = delete;

	static WorldHelper* Instance();
	static void Destroy();

	const RECT& GetGameBounds() const;
	void SetGameBounds(const RECT& bounds);

	const Matrix& GetWorldMatrix() const;
	void SetWorldMatrix(const Matrix& matrix);
private:
	WorldHelper();
	~WorldHelper() = default;
private:
	static WorldHelper* s_instance;

	RECT m_gameBounds;
	Matrix m_world;
};

