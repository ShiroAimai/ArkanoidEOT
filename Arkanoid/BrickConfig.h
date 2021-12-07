#pragma once

enum class BrickType
{
	Red,
	Yellow,
	Blue
};

struct BrickConfig
{
	const int m_points;
	const BrickType m_type;

	BrickConfig(int points, BrickType type) : m_points(points), m_type(type) {}
};

struct RedBrickConfig : public BrickConfig
{
	RedBrickConfig() : BrickConfig(50, BrickType::Red) {}
};

struct YellowBrickConfig : public BrickConfig
{
	YellowBrickConfig() : BrickConfig(75, BrickType::Yellow) {}
};

struct BlueBrickConfig : public BrickConfig
{
	BlueBrickConfig() : BrickConfig(100, BrickType::Blue) {}
};