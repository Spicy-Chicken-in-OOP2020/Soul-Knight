#include "Gun.h"
#include "ShootController.h"

Gun::Gun(ShootController* shootController, int attackNum, String name) :Weapon(attackNum, name)
{
	this->shootController = shootController;

	this->addChild(shootController);

	this->weaponSprite->setPosition(20, -20);

	//¶ÁÈ¡Í¼Ïñ
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Gun.plist", "Gun.png");

	int iFrameNum = 8;
	SpriteFrame* frame = NULL;

	for (int i = 0; i < iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Gun%d.png", i));
		weaponSpriteVec.pushBack(frame);
	}

	//ÉèÖÃ³õÊ¼Í¼Ïñ
	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
}

