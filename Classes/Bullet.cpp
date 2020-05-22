#include "Bullet.h"

//构造函数
Bullet::Bullet()
{
	this->init();
}

bool Bullet::init()
{
	if (!Node::init())
		return false;

	//设置初始状态
	log("Bullet Created;");

	//绑定图片
	Sprite* newSprite = Sprite::create("bullet_6.png");
	this->bindSprite(newSprite);
	//设置运动状态
	this->setActive(false);

	return true;
}

//发射子弹
void Bullet::shoot(Point position)
{
	log("This bullet is shot!");
	//获取初始发射位置
	this->setPosition(position);

	//设定最终地点
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

	//持续移动
	MoveTo* moveTo = MoveTo::create(sqrt(
		(finalX-position.x)*(finalX - position.x)+ 
		(finalY - position.y)*(finalY - position.y))/speed,
		Point(finalX, finalY));
	this->runAction(moveTo);

	//添加移动事件
	this->scheduleUpdate();
}

void Bullet::setActive(bool _isActive)
{
	this->isActive = _isActive;

	//设置可见性
	this->setVisible(_isActive);

	this->actionSprite->setVisible(false);
}

//判断是否到达目标
bool Bullet::isArrive()
{
	//获得当前物体坐标
	Point position = this->getPosition();

	//判断是否触及障碍物
	Size mapSize = GlobalParameter::mapNow->getMapSize();
	Size tileSize = GlobalParameter::mapNow->getTileSize();

	//读取当前所在地图的障碍物层
	TMXLayer* collisionLayer = GlobalParameter::mapNow->getLayer("collision");

	//获得坐标在地图中的格子位置
	Point tiledPos(position.x / tileSize.width, (mapSize.height*tileSize.height - position.y) / tileSize.height);

	if (position.x < 0 || position.y < 0)
	{
		//迷之报错，在这里隐藏掉
		log("What's wrong with you?");
		return true;
	}

	//获取地图格子的唯一表示
	int tiledGid = collisionLayer->getTileGIDAt(tiledPos);

	//图块ID不为空，表示是障碍物
	if (tiledGid !=0 )
	{
		return true;
		
	}

	//判断是否碰到敌人
	/*if (GlobalParameter::monsterManager != nullptr) {
		auto monsterList = GlobalParameter::monsterManager->getMonsterList();
		if (!monsterList.empty()) {
			for (int i = 0; i < monsterList.size(); ++i) {
				Sprite* spriteMonster = monsterList.at(i)->getSprite();
				if (this->getBoundingBox().intersectsRect(spriteMonster->getBoundingBox())) {
					this->setVisible(false);
					monsterList.at(i)->getHurt(1);
				}
			}
		}
	}*/

	return false;
}

void Bullet::bindSprite(Sprite * sprite) {
	//绑定图片
	bulletSprite = sprite;
	this->addChild(bulletSprite);

	//用来播放动画的图片精灵
	this->actionSprite = Sprite::create("bullet_6.png");
	this->addChild(actionSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);

	///*物理body以碰撞*/
	//PhysicsBody* phyBody = PhysicsBody::createCircle(5);
	//phyBody->setGravityEnable(false);

	//sprite->setTag(2);//标识符
	//sprite->setPhysicsBody(phyBody);
}

void Bullet::update(float dt)
{
	//判断是否到达
	if (this->isArrive())
	{
		//停止之前的操作
		this->stopAllActions();
		this->unscheduleUpdate();

		//创建一个回调函数
		//尝试直接加载
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
		
		//this->runAction(action);

		//创建一个回调函数
		CallFunc* callFunc = CallFunc::create(
			[&]() {
			this->setActive(false);
		}
		);

		//组合动作
		Action* actions = Sequence::create(action, callFunc, NULL);
		//动作精灵执行动作
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