#include "Bullet.h"
#include "SafeRoomScene.h"
#include "Monster.h"
#include "Items.h"
//���캯��
Bullet::Bullet():numBullet(1){

	this->init();
}

Bullet::Bullet(int numBullet) :numBullet(numBullet)
{

	this->init();
}

bool Bullet::init()
{
	if (!Node::init())
		return false;

	//���ó�ʼ״̬
	log("Bullet Created;");

	//��ͼƬ
	Sprite* newSprite = Sprite::create(StringUtils::format("bullet_%d.png", numBullet));
	this->bindSprite(newSprite);
	//�����˶�״̬
	this->setActive(false);

	return true;
}

//�����ӵ�
void Bullet::shoot(Point position)
{
	log("This bullet is shot!");
	//��ȡ��ʼ����λ��
	this->setPosition(position);

	//��תͼƬ�Ƕ�

	//�趨���յص�
	if (GlobalParameter::rightSide)
		finalX = position.x + 10000;
	else if (GlobalParameter::leftSide)
		finalX = position.x - 10000;
	else
		finalX = position.x;

	if (GlobalParameter::upSide)
		finalY = position.y + 10000;
	else if (GlobalParameter::downSide)
		finalY = position.y - 10000;
	else
		finalY = position.y;

	//�����ƶ�
	MoveTo* moveTo = MoveTo::create(sqrt(
		(finalX - position.x) * (finalX - position.x) +
		(finalY - position.y) * (finalY - position.y)) / speed,
		Point(finalX, finalY));
	this->runAction(moveTo);

	//����ƶ��¼�
	this->scheduleUpdate();
}
void Bullet::shootForMonster(Point position, Monster* monster) {
	log("This bullet is shot!");
	//��ȡ��ʼ����λ��
	this->setPosition(position);

	//�趨���յص�

	if (monster->getright())
		finalX = position.x + 10000;
	else if (monster->getleft())
		finalX = position.x - 10000;
	else
		finalX = position.x;

	if (monster->getup())
		finalY = position.y + 10000;
	else if (monster->getdown())
		finalY = position.y - 10000;
	else
		finalY = position.y;

	//�����ƶ�
	MoveTo* moveTo = MoveTo::create(sqrt(
		(finalX - position.x) * (finalX - position.x) +
		(finalY - position.y) * (finalY - position.y)) / speed,
		Point(finalX, finalY));
	this->runAction(moveTo);

	//����ƶ��¼�
	this->scheduleUpdate();
}


void Bullet::setActive(bool _isActive)
{
	this->isActive = _isActive;

	//���ÿɼ���
	this->setVisible(_isActive);

	this->actionSprite->setVisible(false);
}

//�ж��Ƿ񵽴�Ŀ��
bool Bullet::isArrive()
{
	//��õ�ǰ��������
	Point position = this->getPosition();

	//�ж��Ƿ񴥼��ϰ���
	Size mapSize = GlobalParameter::mapNow->getMapSize();
	Size tileSize = GlobalParameter::mapNow->getTileSize();

	//��ȡ��ǰ���ڵ�ͼ���ϰ����
	TMXLayer* collisionLayer = GlobalParameter::mapNow->getLayer("collision");

	//��������ڵ�ͼ�еĸ���λ��
	Point tiledPos(position.x / tileSize.width, (mapSize.height * tileSize.height - position.y) / tileSize.height);

	if (position.x < 0 || position.y < 0)
	{
		//��֮�������������ص�
		log("What's wrong with you?");
		return true;
	}

	//��ȡ��ͼ���ӵ�Ψһ��ʾ
	int tiledGid = collisionLayer->getTileGIDAt(tiledPos);

	//ͼ��ID��Ϊ�գ���ʾ���ϰ���
	if (tiledGid != 0)
	{
		return true;

	}

	/*�ж��Ƿ���������,���Ҹ�*/
	if (SafeRoomScene::_monsterManager != nullptr) {
		Vector<Monster*>& monsterList = SafeRoomScene::_monsterManager->getMonsterList();
		for(int i=0;i<monsterList.size();++i)
			
				if (HERO_BULLET == this->getTag() && this->getBoundingBox().intersectsRect(monsterList.at(i)->getBoundingBox())) {
					log("monseter was  hurt !\n");
					monsterList.at(i)->getHurt(1);
					return true;
				}		
	}

	if (MONSTER_BULLET == this->getTag() && this->getBoundingBox().intersectsRect(GlobalParameter::hero->getBoundingBox())) {
		log("hero was hurt !\n");
		GlobalParameter::hero->getHurt(1);
		return true;
	}

	return false;
}

void Bullet::bindSprite(Sprite* sprite) {
	//��ͼƬ
	bulletSprite = sprite;
	this->addChild(bulletSprite);

	//�������Ŷ�����ͼƬ����
	this->actionSprite = Sprite::create("bullet_6.png");
	this->addChild(actionSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);
	//���ý�������
	this->setAnchorPoint(Point(0, 0));
}

void Bullet::update(float dt)
{
	//�ж��Ƿ񵽴�
	if (this->isArrive())
	{
		//ֹ֮ͣǰ�Ĳ���
		this->stopAllActions();
		this->unscheduleUpdate();

		//����һ���ص�����
		//����ֱ�Ӽ���
		SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("Bullet1.plist", "Bullet1.png");

		int iFrameNum = 9;
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameVec;

		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = frameCache->getSpriteFrameByName(StringUtils::format("Bullet1 (%d).png", i));
			frameVec.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(frameVec);
		animation->setLoops(1);
		animation->setDelayPerUnit(0.1f);

		Animate* action = Animate::create(animation);

		//����һ���ص�����
		CallFunc* callFunc = CallFunc::create(
			[&]() {
				this->setActive(false);
			}
		);

		//��϶���
		Action* actions = Sequence::create(action, callFunc, NULL);
		//��������ִ�ж���
		this->actionSprite->setVisible(true);
		this->actionSprite->runAction(actions);

	}
}

bool Bullet::getActive()
{
	return isActive;
}

Sprite* Bullet::getBindSprite()
{
	return this->bulletSprite;
}