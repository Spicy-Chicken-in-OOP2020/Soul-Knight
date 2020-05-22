#include "Monster.h"
#include<ctime>
const int Monster::_moveDirSpeed[4][2] = {
	{-1,1},{-1,-1},{1,-1},{1,1}
};

Monster::Monster() {

}

Monster::~Monster() {

}

bool Monster::init() {
	/*���ڸ�Ϊ���ļ�����*/
	sethp(10);
	setattack(1);
	setMovingSpeed(100);

	//ע���ϰ����ж��¼�
	this->scheduleUpdate();
	this->move();

	return true;
}

void Monster::getHurt(int hurtValue) {
	if (gethp() > hurtValue) {
		sethp(gethp() - hurtValue);
	}
	else {
		sethp(0);
		_isDead = true;
		deadResult();
	}
}

void Monster::attack(Entity* entity) {
	/*�����ӵ�*/
	/*_gun->*/
}

void Monster::deadResult() {
	_sprite->setVisible(false);
}

void Monster::setStartPoint() {
	if (_sprite) {
		//	_sprite->setPosition(Point(800 + CCRANDOM_0_1() * 1000, 200 - CCRANDOM_0_1() * 100));
		this->setPosition(Point(
			2000,800));
	}
}

Point Monster::getPoint() {
	if (_sprite) {
		return this->getPosition();
	}
	return Point(-1, -1);
}

void Monster::move() {
	
	srand(unsigned(time(nullptr)));
	int indexDir = rand() % 4;

	int posX = 1000 * _moveDirSpeed[indexDir][0];
	int posY = 1000 * _moveDirSpeed[indexDir][1];

	MoveBy* moveBy = MoveBy::create(
		sqrt(posX*posX + posY + posY) / getMovingSpeed(),
		Point(posX, posY));

	this->runAction(moveBy);
}

void Monster::update(float dt)
{
	//�ж��ܷ��ƶ�����λ��
	if (this->isStuck())
	{
		//�趨�µ��ƶ��¼�
		this->stopAllActions();
		this->move();
	}
}

bool Monster::isStuck()
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

	return false;
}