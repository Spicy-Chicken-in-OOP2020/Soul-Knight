#ifndef _MOVE_CONTROLLER_H__
#define _MOVE_CONTROLLER_H__

#include "GameController.h"

class MoveController :public GameController {
public:
	CREATE_FUNC(MoveController);
	virtual bool init();
	virtual void update(float dt);
	CC_SYNTHESIZE(int, upSpeed, UpSpeed);
	CC_SYNTHESIZE(int, leftSpeed, LeftSpeed);
	CC_SYNTHESIZE(int, rightSpeed, RightSpeed);
	CC_SYNTHESIZE(int, downSpeed, DownSpeed);
private:

	void registeKeyBoardEvent();
};

#endif