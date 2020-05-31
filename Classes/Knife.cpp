#include "Knife.h"
Knife::Knife(HitController* hitController, int attackNum, String name) :Weapon(attackNum, name)
{
	/*tag*/
	this->setTag(DAO_HERO);

	this->hitController = hitController;

	this->addChild(hitController);

	this->weaponSprite->setPosition(20, -20);

	//��ȡͼ��
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Knife.plist", "Knife.png");

	int iFrameNum = 8;
	SpriteFrame* frame = NULL;

	for (int i = 0; i < iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Knife%d.png", i));
		weaponSpriteVec.pushBack(frame);
	}

	//���ó�ʼͼ��
	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
}

Knife::Knife(int attackNum, String name) :Weapon(attackNum, name) {

	/*tag*/
	this->setTag(DAO_MONSTER);

	this->weaponSprite->setPosition(20, -20);

	//��ȡͼ��
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Knife.plist", "Knife.png");

	int iFrameNum = 8;
	SpriteFrame* frame = NULL;

	for (int i = 0; i < iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Knife%d.png", i));
		weaponSpriteVec.pushBack(frame);
	}

	//���ó�ʼͼ��
	this->weaponSprite->setSpriteFrame(*(weaponSpriteVec.begin()));
}
