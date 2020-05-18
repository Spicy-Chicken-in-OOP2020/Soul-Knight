#include "Bullet.h"

Bullet* Bullet::createBullet(Point position)
{
	Bullet* bullet = new Bullet;
	if (bullet&&bullet->init())
	{
		bullet->autorelease();
		bullet->bulletInit(position);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

bool Bullet::init()
{
	if (!Node::init())
		return false;
	return true;
}

void Bullet::bulletInit(Point position)
{
	//设置初始状态
	isActive = false;
	bullet = Sprite::create("bullet\bullet_6.png");
	bullet->setPosition(position);
	addChild(bullet);
}

//发射子弹
void Bullet::shoot(Point position)
{
	//先随便往一个方向飞
	auto* moveBy = MoveTo::create(speed, Point(position.x + leftSpeed + rightSpeed, position.y + upSpeed + downSpeed));
	this->bullet->runAction(moveBy);
}

void Bullet::setActive(bool _isActive)
{
	this->isActive = _isActive;
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

