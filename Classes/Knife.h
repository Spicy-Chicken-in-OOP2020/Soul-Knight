#ifndef _KNIFE_H__
#define _KNIFE_H__
#include "Weapon.h"
#include "HitController.h"

class Knife :public Weapon
{
public:
	//���캯��
	Knife(HitController* hitController, int attackNum, String name);
	//���������
	HitController* hitController;
};


#endif // !_KNIFE_H__
