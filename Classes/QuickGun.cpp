#include "QuickGun.h"
#include "ShootController.h"

QuickGun::QuickGun(int attackNum, String name) :Weapon(attackNum, name)
{
	ShootController *_shootController = new ShootController(2);

	this->shootController = _shootController;

	this->addChild(shootController);

	this->weaponSprite->setPosition(20, -20);

	//��ȡͼ��
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("QuickGun.plist", "QuickGun.png");

	int iFrameNum = 8;
	SpriteFrame* frame = NULL;

	for (int i = 0; i < iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("QuickGun%d.png", i));
		weaponSpriteVec.pushBack(frame);
	}

	//���ó�ʼͼ��
	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
}

