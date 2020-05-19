#ifndef _SHOOT_CONTROLLER_H__
#define _SHOOT_CONTROLLER_H__


#include"GameController.h"
#include "Bullet.h"
#include "MoveController.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
#define MAX_BULLET_NUM 100

class ShootController :public GameController
{
public:
	CREATE_FUNC(ShootController);
	virtual bool init();
	virtual void bulletUpdate(float dt);

private:
	//ÊÇ·ñÉä»÷×´Ì¬
	bool isShot;
	void registeKeyBoardEvent();
	Bullet* bulletList[MAX_BULLET_NUM];
};


#endif // !_SHOOT_CONTROLLER_H__
