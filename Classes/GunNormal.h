#ifndef _GUN_NORMAL_H__
#define _GUN_NORMAL_H__
#include "BulletManager.h"
class GunNormal:public WeaponEntity
{
private:
	//ǹ֧����Ҫ��һ���ӵ�������
	BulletManager* bulletManager;

public:
	virtual bool init(Sprite* sprite);

	//ǹ֧����
	void shoot();
};

#endif // !_GUN_NORMAL_H__

