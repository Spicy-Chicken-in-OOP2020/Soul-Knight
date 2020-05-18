
#include"GameController.h"
#include "Bullet.h"
#include "MoveController.h"
#include "Hero.h"

#define MAX_BULLET_NUM 20

class ShootController:public GameController
{
public:
	CREATE_FUNC(ShootController);
	virtual bool init();
	virtual void update(float dt);

private:
	//ÊÇ·ñÉä»÷×´Ì¬
	bool isShot;
	void registeKeyBoardEvent();
	Bullet* bulletList[MAX_BULLET_NUM];
};

