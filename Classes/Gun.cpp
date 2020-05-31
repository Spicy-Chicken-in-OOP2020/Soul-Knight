#include "Gun.h"
#include "ShootController.h"

//Gun::Gun(int attackNum, String name) :Weapon(attackNum, name)
//{
//	ShootController* _shootController = new ShootController(1);
//
//	this->shootController = _shootController;
//
//	this->addChild(shootController);
//
//	this->weaponSprite->setPosition(20, -20);
//
//	//��ȡͼ��
//	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
//	frameCache->addSpriteFramesWithFile("Gun.plist", "Gun.png");
//
//	int iFrameNum = 8;
//	SpriteFrame* frame = NULL;
//
//	for (int i = 0; i < iFrameNum; i++)
//	{
//		frame = frameCache->getSpriteFrameByName(StringUtils::format("Gun%d.png", i));
//		weaponSpriteVec.pushBack(frame);
//	}
//
//	//���ó�ʼͼ��
//	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
//}

/*monster*/
Gun::Gun(int attackNum, String name) :Weapon(attackNum, name) {

	ShootController* _shootController = new ShootController(1);

	this->shootController = _shootController;

	this->addChild(shootController);
	//��ȡͼ��
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Gun.plist", "Gun.png");

	int iFrameNum = 8;
	SpriteFrame* frame = NULL;

	for (int i = 0; i < iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Gun%d.png", i));
		weaponSpriteVec.pushBack(frame);
	}

	//���ó�ʼͼ��
	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
}
