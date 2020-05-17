#include "MonsterManager.h"
#include"Monster.h"
MonsterManager::MonsterManager():_monsterTimes(0) {

}

MonsterManager::~MonsterManager() {

}

MonsterManager* MonsterManager::createMonsterManagerWithLevel(int curLevel) {
	MonsterManager* monsterManager = new MonsterManager();

	if (monsterManager && monsterManager->initWithLevel(curLevel)) {
		monsterManager->autorelease();
	}
	else {
		CC_SAFE_DELETE(monsterManager);
	}

	return monsterManager;
}

bool MonsterManager::initWithLevel(int curLevel) {
	/*更新怪物波数*/
	this->schedule(schedule_selector(MonsterManager::showMonster), 0);
	return true;
}

Vector<Monster*> MonsterManager::getMonsterList() {
	return _monsterList;
}

void MonsterManager::createMonsters(int curLevel) {
	/*随机生成怪物对象*/
	Monster* monster = nullptr;
	Sprite* sprite = nullptr;

	for (int i = 0; i < MONSTER_NUM; ++i) {
		monster = Monster::create();
		monster->bindSprite(Sprite::create("boss.png"));
		monster->setStartPoint();

		_monsterList.pushBack(monster);
	}
}

void MonsterManager::showMonster(float dt) {
	if (_monsterList.size() == 0&&_monsterTimes<FRESH_TIMES) {
		++_monsterTimes;
		createMonsters(_monsterTimes);
	}
	else {
		for (auto monster : _monsterList)
			if (monster->isDead())
				_monsterList.eraseObject(monster);
			else
				monster->move();
	}
}
