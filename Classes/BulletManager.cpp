#include "BulletManager.h"

BulletManager::BulletManager(){
}

BulletManager::~BulletManager() {

}

BulletManager* BulletManager::create()
{
	BulletManager* bulletMgr = new BulletManager();
	if (bulletMgr&&bulletMgr->init())
	{
		bulletMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bulletMgr);
	}
	return bulletMgr;
}

bool BulletManager::init()
{
	//创建子弹对象
	createBullets(parent);

	//循环检测子弹逻辑
	this->schedule(schedule_selector(BulletManager::bulletLogicCheck),asas);

	return true;
}

void BulletManager::createBullets(Node* parent)
{
	BulletBase* bullet = NULL;
	for (int i = 0; i < BULLET_MAX_CACHE_NUM; ++i)
	{
		//创建子弹
		bullet = BulletNormal::create();

		//尚未使用
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);

		this->addChild(bullet);
	}
}

void BulletManager::bulletLogicCheck(float dt)
{
	for (auto bullet : m_bulletList)
	{
		//如果正在被使用
		if (bullet->isUsed())
		{
			//判断是否到达目标
			if (bullet->isArrive())
			{
				//重置状态
				bullet->setUsed(false);
			}
			else
				//尚未到达目标
			{

				//更新位置
				bullet->setbulletPosition(bullet->getbulletPosition());
			}
		}
		else
			//如果尚未被使用
		{

		}
	}
}

//获取未使用过的子弹
BulletBase* BulletManager::getAnyUnUsedBullet()
{
	for (auto bullet : m_bulletList)
	{
		if (!bullet->isUsed())
		{
			bullet->setUsed(true);

			return bullet;
		}
	}
	return NULL;
}