#include "GameController.h"

class MoveController :public GameController {
public:
	CREATE_FUNC(MoveController);
	virtual bool init();
	virtual void update(float dt);
	void setUpSpeed(int speed);
	void setLeftSpeed(int speed);
	void setRightSpeed(int speed);
	void setDownSpeed(int speed);
private:
	int upSpeed;
	int leftSpeed;
	int rightSpeed;
	int downSpeed;
	void registeKeyBoardEvent();
};