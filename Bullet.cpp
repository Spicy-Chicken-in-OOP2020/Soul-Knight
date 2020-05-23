#include "Bullet.h"
#include "SafeRoomScene.h"

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
	//��ȡ��ʼ����λ��
	this->setPosition(position);

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
		(finalX-position.x)*(finalX - position.x)+ 
		(finalY - position.y)*(finalY - position.y))/speed,
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
	Point tiledPos(position.x / tileSize.width, (mapSize.height*tileSize.height - position.y) / tileSize.height);

	if (position.x < 0)
	{
		//��֮�������������ص�
		log("What's wrong with you?");
		return true;
	}

	//��ȡ��ͼ���ӵ�Ψһ��ʾ
	int tiledGid = collisionLayer->getTileGIDAt(tiledPos);

	//ͼ��ID��Ϊ�գ���ʾ���ϰ���
	if (tiledGid !=0 )
	{
		return true;
		
	}


	//�ж��Ƿ���������
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

	//���˿�Ѫ

	return false;
}

void Bullet::bindSprite(Sprite * sprite) {
	//��ͼƬ
	bulletSprite = sprite;

	this->addChild(bulletSprite);

	Size size = bulletSprite->getContentSize();
	this->setContentSize(size);
	this->setAnchorPoint(Point(0, 0));
}

void Bullet::update(float dt)
{
	//�ж��Ƿ񵽴�
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