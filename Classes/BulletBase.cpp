#include "BulletBase.h"
BulletBase::BulletBase()
{
	m_isUsed = false;
	//�ٶ�
	m_iSpeed = 1;
	m_isAtkValue = 1;
}

BulletBase::~BulletBase() {

}

void BulletBase::setUsed(bool isUsed)
{
	this->m_isUsed = isUsed;
	//�����Ƿ���ʹ�����ÿɼ���
	setVisible(isUsed);
}

bool BulletBase::isUsed()
{
	return this->m_isUsed;
}

bool BulletBase::isArrive()
{
	//�����ж��Ƿ��������ϰ���
	Hero* hero = (Hero*)this->getParent()->getParent()->getParent();
	//��ȡ��ͼ
	TMXTiledMap* map = hero->getPosition();
	
	//��ȡ


	//����ж��Ƿ�͹�����Ӵ�

	return m_isArrive;
}