#ifndef _QUICKGUN_H__
#define _QUICKGUN_H__

#include "Weapon.h"
class ShootController;

class QuickGun :public Weapon
{
public:
	//���캯��
	QuickGun(int attackNum, String name);
	//���������
	ShootController* shootController;
};


#endif // !_QUICKGUN_H__
