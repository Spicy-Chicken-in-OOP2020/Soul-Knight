#include "Bullet.h"
#include "SafeRoomScene.h"

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

	if (position.x < 0)
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
	if (SafeRoomScene::_monsterManager!=nullptr) {
		auto monsterList = SafeRoomScene::_monsterManager->getMonsterList();
		if (!monsterList.empty()) {
			for (int i = 0; i < monsterList.size(); ++i) {
				
				if (this->getBoundingBox().intersectsRect(monsterList.at(i)->getBoundingBox())) {
					this->setVisible(false);
					monsterList.at(i)->getHurt(1);
				}

			}
		}
	}

	//敌人扣血

	return false;
}

void Bullet::bindSprite(Sprite * sprite) {
	//绑定图片
	bulletSprite = sprite;

	this->addChild(bulletSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);
	this->setAnchorPoint(Point(0, 0));
}

void Bullet::update(float dt)
{
	//判断是否到达
	if (this->isArrive())
	{
		this->stopAllActions();
		this->unscheduleUpdate();
		this->setActive(false);
	}
	
}

bool Bullet::getActive()
{
	return isActive;
}