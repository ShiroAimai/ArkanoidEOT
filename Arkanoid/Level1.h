#pragma once
#include "BaseLevel.h"

class Ball;

class Level1 : public BaseLevel
{

protected:
	virtual void GetLevelObjects(std::vector<BaseObject*>& GameObjects) override;

private:
	/**
	 * Select one of the following configurations
	*/
	void GetRandomLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects);

	/**
	 * All Red bricks
	 * 3 rows
	 */
	void GetEasyLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects);
	/**
	 * Yellow bricks in the first and last row, first and last column
	 * Red bricks in the other ones
	 * 3 rows
	 */
	void GetNormalLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects);
	/**
	 * Blue bricks in the first and last row, first and last column
	 * Yellow bricks in the other ones
	 * 4 rows
	 */
	void GetHardLevel(Ball* LevelBall, std::vector<BaseObject*>& GameObjects);
};

