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
	/*后期改为从文件导入*/
	sethp(10);
	setattack(1);
	setMovingSpeed(100);

	//注册障碍物判定事件
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
	/*发射子弹*/
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
	//判断能否移动到此位置
	if (this->isStuck())
	{
		//设定新的移动事件
		this->stopAllActions();
		this->move();
	}
}

bool Monster::isStuck()
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
	if (tiledGid != 0)
	{
		return true;
	}

	return false;
}