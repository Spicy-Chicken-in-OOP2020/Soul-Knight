#include "GunNormal.h"

bool GunNormal::init(Sprite* sprite)
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!sprite);

		bindSprite(sprite);

		//�����ӵ�������
		bulletManager = BulletManager::create();
		this->addChild(bulletManager);
		bRet = true;
	} while (0);

	return bRet;
}

void GunNormal::shoot()
{
	//���ӵ���������ȡ��һ��δ��ʹ�õ��ӵ�����
	BulletBase* bullet = bulletManager->getAnyUnUsedBullet();

	if (bullet != NULL)
	{
		//��ȡ��������������ĵ�ǰ����
		
	}
}