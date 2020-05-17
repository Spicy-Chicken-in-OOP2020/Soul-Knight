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
		_sprite->setPosition(Point(800 + CCRANDOM_0_1() * 2000, 200 - CCRANDOM_0_1() * 100));
	}
}

Point Monster::getPoint() {
	if (_sprite) {
		return _sprite->getPosition();
	}
	return Point(-1, -1);
}

void Monster::move() {
	srand(unsigned(time(nullptr)));
	int indexDir = rand() % 4;

	_sprite->setPosition(
		getPoint().x + _moveDirSpeed[indexDir][0],
		getPoint().y + _moveDirSpeed[indexDir][0]);

}