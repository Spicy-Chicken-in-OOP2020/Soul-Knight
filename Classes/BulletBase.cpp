#include "BulletBase.h"
BulletBase::BulletBase()
{
	m_isUsed = false;
	//速度
	m_iSpeed = 1;
	m_isAtkValue = 1;
}

BulletBase::~BulletBase() {

}

void BulletBase::setUsed(bool isUsed)
{
	this->m_isUsed = isUsed;
	//根据是否在使用设置可见性
	setVisible(isUsed);
}

bool BulletBase::isUsed()
{
	return this->m_isUsed;
}

bool BulletBase::isArrive()
{
	//首先判断是否触碰到了障碍物
	Hero* hero = (Hero*)this->getParent()->getParent()->getParent();
	//获取地图
	TMXTiledMap* map = hero->getPosition();
	
	//获取


	//其次判断是否和怪物相接触

	return m_isArrive;
}