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
	//�����ӵ�����
	createBullets(parent);

	//ѭ������ӵ��߼�
	this->schedule(schedule_selector(BulletManager::bulletLogicCheck),asas);

	return true;
}

void BulletManager::createBullets(Node* parent)
{
	BulletBase* bullet = NULL;
	for (int i = 0; i < BULLET_MAX_CACHE_NUM; ++i)
	{
		//�����ӵ�
		bullet = BulletNormal::create();

		//��δʹ��
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);

		this->addChild(bullet);
	}
}

void BulletManager::bulletLogicCheck(float dt)
{
	for (auto bullet : m_bulletList)
	{
		//������ڱ�ʹ��
		if (bullet->isUsed())
		{
			//�ж��Ƿ񵽴�Ŀ��
			if (bullet->isArrive())
			{
				//����״̬
				bullet->setUsed(false);
			}
			else
				//��δ����Ŀ��
			{

				//����λ��
				bullet->setbulletPosition(bullet->getbulletPosition());
			}
		}
		else
			//�����δ��ʹ��
		{

		}
	}
}

//��ȡδʹ�ù����ӵ�
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