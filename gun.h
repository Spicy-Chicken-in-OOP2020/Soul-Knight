#ifndef _GUN_H__
#define _GUN_H__

#include "Weapon.h"
class ShootController;

class Gun :public Weapon
{
public:
	//构造函数
	Gun(ShootController* shootController, int attackNum, String name);

	Gun(int attackNum, String name);
	//射击管理器
	ShootController* shootController;
};

#endif // !_GUN_H__
