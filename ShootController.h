#ifndef _SHOOT_CONTROLLER_H__
#define _SHOOT_CONTROLLER_H__

#define HERO_BULLET 1
#define MONSTER_BULLET 2

#include "GameController.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

#define MAX_BULLET_NUM 50

class ShootController :public GameController
{
public:
	CREATE_FUNC(ShootController);
	virtual bool init();
	virtual void bulletUpdate(float dt);

	static ShootController* createForMonster();
	bool initForMonsters();
	void setIsShot(bool isShot);
	void bulletUpdateMonster(float dt);

private:
	//ÊÇ·ñÉä»÷×´Ì¬
	bool isShot;

	void registeKeyBoardEvent();
	Bullet* bulletList[MAX_BULLET_NUM];
};


#endif // !_SHOOT_CONTROLLER_H__
