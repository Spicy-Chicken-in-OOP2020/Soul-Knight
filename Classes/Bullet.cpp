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
	//���ó�ʼ״̬
	isActive = false;
	bullet = Sprite::create("bullet\bullet_6.png");
	bullet->setPosition(position);
	addChild(bullet);
}

//�����ӵ�
void Bullet::shoot(Point position)
{
	//�������һ�������
	auto* moveBy = MoveTo::create(speed, Point(position.x + leftSpeed + rightSpeed, position.y + upSpeed + downSpeed));
	this->bullet->runAction(moveBy);
}

void Bullet::setActive(bool _isActive)
{
	this->isActive = _isActive;
	this->setVisible(_isActive);

}

//�ж��Ƿ񵽴�Ŀ��
bool Bullet::isArrive()
{
	//�ж��Ƿ񴥼��ϰ���

	//�ж��Ƿ���������

	//���˿�Ѫ

	return false;
}

