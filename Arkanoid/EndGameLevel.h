#pragma once
#include "BaseLevel.h"

class EndGameLevel : public BaseLevel
{
public:
	virtual DirectX::XMVECTORF32 GetLevelBackground() const { return DirectX::Colors::DarkSlateBlue; }

protected:
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) override;
};

