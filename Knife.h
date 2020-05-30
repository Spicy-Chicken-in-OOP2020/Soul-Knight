#ifndef _KNIFE_H__
#define _KNIFE_H__
#include "Weapon.h"
#include "HitController.h"
#define DAO_HERO 1
#define DAO_MONSTER 2

class Knife :public Weapon
{
public:
	//构造函数
	Knife(HitController* hitController, int attackNum, String name);

	Knife(int attackNum, String name);
	//射击管理器
	HitController* hitController;
};


#endif // !_KNIFE_H__
