#include "GunNormal.h"

bool GunNormal::init(Sprite* sprite)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!sprite);

		bindSprite(sprite);

		//创建子弹管理器
		bulletManager = BulletManager::create();
		this->addChild(bulletManager);
		bRet = true;
	} while (0);

	return bRet;
}

void GunNormal::shoot()
{
	//从子弹管理器中取出一个未被使用的子弹对象
	BulletBase* bullet = bulletManager->getAnyUnUsedBullet();

	if (bullet != NULL)
	{
		//获取武器所附属对象的当前朝向
		
	}
}