#ifndef _GUN_H__
#define _GUN_H__

#include "Weapon.h"
class ShootController;

class Gun :public Weapon
{
public:
	//���캯��
	Gun(ShootController* shootController, int attackNum, String name);

	Gun(int attackNum, String name);
	//���������
	ShootController* shootController;
};

#endif // !_GUN_H__
