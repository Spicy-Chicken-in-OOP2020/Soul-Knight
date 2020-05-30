#include "MonsterManager.h"
#include "SafeRoomScene.h"

MonsterManager::MonsterManager() :_monsterTimes(0) {

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
	this->schedule(schedule_selector(MonsterManager::showMonster), 1);
	return true;
}

Vector<Monster*>& MonsterManager::getMonsterList() {
	return _monsterList;
}

void MonsterManager::createMonsters(int curLevel) {
	/*随机生成怪物对象*/
	Monster* monster = nullptr;
	Sprite* sprite = nullptr;

	TMXObjectGroup* monsterStartPointGroup = SafeRoomScene::_safeRoomMap->getObjectGroup("monster_1");
	ValueMap monsterStartPoint;

	int monsterNo = 1;
	while ((monsterStartPoint = monsterStartPointGroup->getObject(StringUtils::format("monster%d", monsterNo))).size()) {
		log("A monster is created !");
		++monsterNo;

		/*monster起始点*/
		float X = monsterStartPoint.at("x").asFloat();
		float Y = monsterStartPoint.at("y").asFloat();

		/*monster*/
		monster = Monster::create();
		monster->bindSprite(Sprite::create("Knight1Right.png"));
		
		monster->settBirthPlace(Point(X, Y));

		monster->setPosition(X, Y);
		this->addChild(monster);
		/*出场动画*/
		monster->birthAnimate();
		_monsterList.pushBack(monster);

	}

}

void MonsterManager::showMonster(float dt) {
	if (_monsterList.size() == 0 && _monsterTimes < FRESH_TIMES) {
		++_monsterTimes;
		createMonsters(_monsterTimes);
	}
	else {
		for (int i=0;i<_monsterList.size();++i)
			if (_monsterList. at(i)&& _monsterList.at(i)->isDead()) {
				_monsterList.at(i)->removeFromParentAndCleanup(true);
				_monsterList.eraseObject(_monsterList.at(i), false);
			}
			/*else if (_monsterList.at(i)) {
				_monsterList.at(i)->update(dt);
			}*/
	}
}
