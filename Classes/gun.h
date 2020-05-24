#ifndef _GUN_H__
#define _GUN_H__

#include "Weapon.h"
#include "ShootController.h"

class Gun :public Weapon
{
public:
	//构造函数
	Gun(ShootController* shootController, int attackNum, String name);
	//射击管理器
	ShootController* shootController;
};

#endif // !_GUN_H__
