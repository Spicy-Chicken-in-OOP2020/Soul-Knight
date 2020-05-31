#ifndef _QUICKGUN_H__
#define _QUICKGUN_H__

#include "Weapon.h"
class ShootController;

class QuickGun :public Weapon
{
public:
	//构造函数
	QuickGun(int attackNum, String name);
	//射击管理器
	ShootController* shootController;
};


#endif // !_QUICKGUN_H__
