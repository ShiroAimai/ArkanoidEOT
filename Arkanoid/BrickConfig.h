#pragma once
#include <DirectXMath.h>
#include <memory>
#include <vector>

enum class BrickType
{
	Red = 0,
	Yellow,
	Blue,
	Size
};

struct BrickConfig
{
	int m_lifePoints;
	BrickType m_type;
	DirectX::XMVECTORF32 m_color;

	BrickConfig(int lifePoints, DirectX::XMVECTORF32 color, BrickType type);
	virtual ~BrickConfig();;

	BrickConfig(const BrickConfig& Other);
	BrickConfig& operator=(const BrickConfig& Other);
};

struct RedBrickConfig : public BrickConfig
{
	RedBrickConfig() : BrickConfig(0, DirectX::Colors::Red, BrickType::Red) {}
};

struct YellowBrickConfig : public BrickConfig
{
	YellowBrickConfig() : BrickConfig(1, DirectX::Colors::Yellow, BrickType::Yellow) {}
};

struct BlueBrickConfig : public BrickConfig
{
	BlueBrickConfig() : BrickConfig(2, DirectX::Colors::Blue, BrickType::Blue) {}
};

class BrickHelper
{
public:
	static BrickHelper* Instance();

	std::shared_ptr<BrickConfig> GetBrickConfigByType(BrickType type);
	std::shared_ptr<BrickConfig> GetBrickConfigByLifePoints(int lifePoints);
private:
	BrickHelper();

	std::vector<std::shared_ptr<BrickConfig>> m_configs;
	static BrickHelper* s_instance;
};