#include "Bullet.h"

//���캯��
Bullet::Bullet()
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
	Sprite* newSprite = Sprite::create("bullet_6.png");
	this->bindSprite(newSprite);
	//�����˶�״̬
	this->setActive(false);

	return true;
}

//�����ӵ�
void Bullet::shoot(Point position)
{
	log("This bullet is shot!");
	//�趨��ʼ����λ��
	this->setPosition(position);

	//�趨���յص�
	finalX = position.x+10000;
	finalY = position.y+10000;

	//����ƶ��¼�
	this->scheduleUpdate();
}

void Bullet::setActive(bool _isActive)
{
	this->isActive = _isActive;
	//���ÿɼ���
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

void Bullet::bindSprite(Sprite * sprite) {
	//��ͼƬ
	bulletSprite = sprite;
	this->addChild(bulletSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);
}

void Bullet::update(float dt)
{
	//�ж��Ƿ񵽴�
	if (this->isArrive())
	{
		this->unscheduleUpdate();
		this->setActive(false);
	}
	//�����ƶ�
	MoveTo* moveTo = MoveTo::create(100, Point(0, 0));
	this->runAction(moveTo);
}

bool Bullet::getActive()
{
	return isActive;
}