#ifndef _KNIFE_H__
#define _KNIFE_H__
#include "Weapon.h"
#include "HitController.h"

class Knife :public Weapon
{
public:
	//构造函数
	Knife(HitController* hitController, int attackNum, String name);
	//射击管理器
	HitController* hitController;
};


#endif // !_KNIFE_H__
