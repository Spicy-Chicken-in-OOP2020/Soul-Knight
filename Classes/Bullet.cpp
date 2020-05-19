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
	//设定初始发射位置
	this->setPosition(position);

	//设定最终地点
	finalX = position.x+10000;
	finalY = position.y+10000;

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
	//判断是否触及障碍物

	//判断是否碰到敌人

	//敌人扣血

	return false;
}

void Bullet::bindSprite(Sprite * sprite) {
	//绑定图片
	bulletSprite = sprite;
	this->addChild(bulletSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);
}

void Bullet::update(float dt)
{
	//判断是否到达
	if (this->isArrive())
	{
		this->unscheduleUpdate();
		this->setActive(false);
	}
	//持续移动
	MoveTo* moveTo = MoveTo::create(100, Point(0, 0));
	this->runAction(moveTo);
}

bool Bullet::getActive()
{
	return isActive;
}