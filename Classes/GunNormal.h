#ifndef _GUN_NORMAL_H__
#define _GUN_NORMAL_H__
#include "BulletManager.h"
class GunNormal:public WeaponEntity
{
private:
	//枪支中需要有一个子弹管理器
	BulletManager* bulletManager;

public:
	virtual bool init(Sprite* sprite);

	//枪支攻击
	void shoot();
};

#endif // !_GUN_NORMAL_H__

