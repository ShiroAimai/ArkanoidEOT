#include "pch.h"
#include "BrickConfig.h"

BrickConfig::BrickConfig(int lifePoints, DirectX::XMVECTORF32 color, BrickType type)
	: m_lifePoints(lifePoints), m_type(type), m_color(color)
{

}

BrickConfig::BrickConfig(const BrickConfig& Other) : m_lifePoints(Other.m_lifePoints), m_color(Other.m_color), m_type(Other.m_type)
{
	
}

BrickConfig& BrickConfig::operator=(const BrickConfig& Other)
{
	if (this != &Other)
	{
		m_lifePoints = Other.m_lifePoints;
		m_color = Other.m_color;
		m_type = Other.m_type;
	}
	
	return *this;
}

BrickConfig::~BrickConfig()
{

}

BrickHelper::BrickHelper()
{
	m_configs.push_back(std::make_shared<RedBrickConfig>());
	m_configs.push_back(std::make_shared<YellowBrickConfig>());
	m_configs.push_back(std::make_shared<BlueBrickConfig>());
}

BrickHelper* BrickHelper::s_instance = nullptr;

BrickHelper* BrickHelper::Instance()
{
	if (!s_instance)
		s_instance = new BrickHelper();
	return s_instance;
}

std::shared_ptr<BrickConfig> BrickHelper::GetBrickConfigByType(BrickType type)
{
	return GetBrickConfigByLifePoints((int) type);
}

std::shared_ptr<BrickConfig> BrickHelper::GetBrickConfigByLifePoints(int lifePoints)
{
	if(lifePoints < 0 || lifePoints >= (int)BrickType::Size) return nullptr;

	return m_configs[lifePoints];
}
