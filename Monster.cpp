#include "Monster.h"
#include <ctime>
#include "SafeRoomScene.h"
#include "ShootController.h"
#include "HitController.h"
#include <algorithm>
#include "Items.h"


Monster::Monster() :
	_thinkTime(1500),
	_weapon(nullptr),
	_weaponTag(0),
	_moveSpeed(2),
	_up(false),
	_down(false),
	_left(false),
	_right(false),
	_collisionLayer(nullptr),
	_collision1Layer(nullptr),
	_outsideLayer(nullptr),
	_canLayer(nullptr),
	_attackR(0),
	_actionSprite(nullptr),
	_moveTo(nullptr),
	_lastPoint(-1, -1)
{}

Monster::~Monster() {

}

bool Monster::init() {
	srand(unsigned(time(nullptr)));
	/*后期改为从文件导入*/
	sethp(10);
	setattack(1);

	/*读取当前所在地图的障碍物层*/
	_collisionLayer = GlobalParameter::mapNow->getLayer("collision");
	_collision1Layer = GlobalParameter::mapNow->getLayer("collision2");
	_outsideLayer = GlobalParameter::mapNow->getLayer("outside");
	_canLayer = GlobalParameter::mapNow->getLayer("can");

	/*武器*/
	auto possible = rand_0_1();
	if (possible < 0.5) {
		_weaponTag = GUN_TAG;
		_attackR = 500;
	}
	else {
		_weaponTag = DAO_TAG;
		_attackR = 310;
	}
	initWithWeaponTag(_weaponTag);

	//this->setVisible(false);
	/*随机初始化方向*/
	float ran1 = rand() % 10 / 10.0;
	float ran2 = rand() % 10 / 10.0;

	if (ran1 < 0.5) {
		setup(true);
	}
	else {
		setdown(true);
	}

	if (ran2 < 0.5) {
		setright(true);
	}
	else {
		setleft(true);
	}

	return true;
}

void Monster::initWithWeaponTag(int tag) {
	switch (tag) {
	case GUN_TAG:
		_weapon = new Gun(2, "gun");
		break;
	case DAO_TAG:
		_weapon = new Knife(2, "knife");
		break;
	}

	this->addChild(_weapon);

	CCString weaponType = typeid(*_weapon).name();
	/*添加控制器*/
	if (weaponType._string == "class Gun") {
		Gun* gun = dynamic_cast<Gun*>(_weapon);
		gun->shootController = ShootController::createForMonster();
		gun->addChild(gun->shootController);
		gun->shootController->setMyControlListener(this);
	}
	else if (weaponType._string == "class Knife") {
		Knife* knife = dynamic_cast<Knife*>(_weapon);
		knife->hitController = HitController::createForMonster();
		knife->addChild(knife->hitController);
		knife->hitController->setMyControlListener(this);
	}
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
	if (entity == nullptr) {
		return;
	}

	switch (_weaponTag) {
	case GUN_TAG:
		dynamic_cast<Gun*>(_weapon)->shootController->setIsShot(true);
		break;
	case DAO_TAG:
		dynamic_cast<Knife*>(_weapon)->hitController->setIsHit(true);
		break;
	}
}

void Monster::deadResult() {
	srand(unsigned(time(nullptr)));
	/*这句话别乱改*/
	this->setVisible(false);
	/*掉落道具*/
	float poss = CCRANDOM_0_1();
	if (poss < 0.5) {
		auto item = Items::createItems(HP_ADD_TAG);
		item->setPosition(this->getPosition());
		dynamic_cast<Layer*>(this->getParent()->getParent())->addChild(item, 2);
	}
	else {
		auto item = Items::createItems(MP_ADD_TAG);
		item->setPosition(this->getPosition());
		dynamic_cast<Layer*>(this->getParent()->getParent())->addChild(item, 2);
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

	Point posThis = this->getPosition();

	/*移动*/
	int dx = 0, dy = 0;

	if (getup()) {
		dy = getmoveSpeed();
		if (getleft()) {
			dx = -getmoveSpeed();
		}
		else if (getright()) {
			dx = getmoveSpeed();
		}
	}
	else if (getdown()) {
		dy = -getmoveSpeed();
		if (getleft()) {
			dx = -getmoveSpeed();
		}
		else if (getright()) {
			dx = getmoveSpeed();
		}
	}
	else {
		if (getleft()) {
			dx = -getmoveSpeed();
		}
		else if (getright()) {
			dx = getmoveSpeed();
		}
	}

	/*移动*/
	Point objPos = Point(posThis.x + dx, posThis.y + dy);

	if (isStuck(objPos))
		return;

	this->setlastPoint(posThis);
	this->setPosition(objPos);

}

void Monster::update(float dt) {
	/*计时缓冲*/
	static int iCount1 = 0;
	static int iCount2 = 0;

	setmoveSpeed(1);

	srand(unsigned(time(nullptr)));

	/*获取移动方向*/
	Point posHero = SafeRoomScene::_hero->getPosition();
	Point posThis = this->getPosition();
	/*攻击范围*/
	Rect* attackRect = new Rect
	(this->getPosition().x - _attackR / 2,
		this->getPosition().y - _attackR / 2,
		_attackR, _attackR);

	/*靠近英雄*/
	if (attackRect->containsPoint(SafeRoomScene::_hero->getPosition())) {
		log("into attack range !\n");
		/*卡住优先*/
		if (isNotMove(getlastPoint(), posThis)) {
			if (iCount2 < 5)
				++iCount2;
			else {
				iCount2 = 0;
				log("Not move1 !\n");
				this->changeDirection();
			}
		}
		else {
			if (iCount1 < 15)
				++iCount1;
			else {
				iCount1 = 0;

				setup(false);
				setdown(false);
				setleft(false);
				setright(false);
				if (posHero.x >= posThis.x) {
					setright(true);
					if (posHero.y >= posThis.y)
						setup(true);
					else
						setdown(true);
				}
				else {
					setleft(true);
					if (posHero.y >= posThis.y)
						setup(true);
					else
						setdown(true);
				}
			}
		}

		/*攻击 */
		this->attack(SafeRoomScene::_hero);
	}
	/*移动范围*/
	else {

		this->unattack();

		if (isNotMove(getlastPoint(), posThis)) {
			if (iCount2 < 5)
				++iCount2;
			else {
				iCount2 = 0;
				log("Not move2 !\n");
				this->changeDirection();
			}
		}
		else {
			if (iCount1 < 15)
				++iCount1;
			else {
				iCount1 = 0;

				setup(false);
				setdown(false);
				setleft(false);
				setright(false);

				float ran1 = rand() % 10 / 10.0;
				float ran2 = rand() % 10 / 10.0;
				if (ran1 < 0.5) {
					setup(true);
				}
				else {
					setdown(true);
				}
				if (ran2 < 0.5) {
					setright(true);
				}
				else {
					setleft(true);
				}
			}
		}
	}

	this->move();
}

bool Monster::setTagPosition(int x, int y) {
	return true;
}

Point Monster::getTagPosition() {
	return this->getPosition();
}

bool  Monster::isStuck(const Point& objPos) {
	/*层大小*/
	auto layerSize = _collisionLayer->getLayerSize();

	//判断是否触及障碍物
	Size mapSize = GlobalParameter::mapNow->getMapSize();
	Size tileSize = GlobalParameter::mapNow->getTileSize();

	/*转换为地图上的坐标系*/
	Point tilesPos(objPos.x / tileSize.width, (mapSize.height * tileSize.height - objPos.y) / tileSize.height);

	if (tilesPos.x < 0 || tilesPos.y < 0 || tilesPos.x >= layerSize.width || tilesPos.y >= layerSize.height) {
		log("bad ways1\n");

		return true;
	}

	/*获取地图格子的唯一表示*/
	int tiledGidcollsion = _collisionLayer->getTileGIDAt(tilesPos);
	int tiledGidcollsion1 = _collision1Layer->getTileGIDAt(tilesPos);
	int tiledGidOutside = _outsideLayer->getTileGIDAt(tilesPos);
	int tiledGidCan = _canLayer->getTileGIDAt(tilesPos);


	//图块ID不为空，表示是障碍物
	if (tiledGidcollsion != 0 || tiledGidcollsion1 != 0 || tiledGidOutside != 0 || tiledGidCan != 0) {

		log("bad ways2\n");

		return true;
	}

	return false;
}

void Monster::birthAnimate() {
	/*播放动画用的精灵 */
	//_actionSprite = Sprite::create("KnightImage.png");
	//_actionSprite->setVisible(false);
	//_actionSprite->setTag(2);
	//this->addChild(_actionSprite);

	////this->addChild(_actionSprite);

	///*加载出场动画*/
	//SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	//spriteFrameCache->addSpriteFramesWithFile("Appear.plist", "Appear.png");

	//int frameNum = 30;
	//SpriteFrame* frame = nullptr;
	//Vector<SpriteFrame*> frameVec;

	//for (int i = 1; i <= frameNum; ++i) {
	//	frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format("Appear (%d).png", i));
	//	frameVec.pushBack(frame);
	//}

	//Animation* animation = Animation::createWithSpriteFrames(frameVec);
	//animation->setLoops(1);
	//animation->setDelayPerUnit(0.1f);

	//Animate* animate = Animate::create(animation);

	///*动作回调函数*/
	//auto callFunc = CallFunc::create([&]() {
	//	this->getChildByTag(2)->setVisible(false);
	//	this->getChildByTag(2)->removeFromParentAndCleanup(true);
	//	this->setVisible(true);
	//	}
	//);

	//Action* sequence = Sequence::create(animate, callFunc, nullptr);
	//_actionSprite->runAction(sequence);

	this->scheduleUpdate();
}

Point Monster::getBirthPlace() {
	return this->_birthPlace;
}

void Monster::settBirthPlace(const Point& pos) {
	this->_birthPlace = pos;
}

void Monster::changeDirection() {
	setmoveSpeed(3);

	if (getup()) {
		setup(false);
		setdown(true);
	}
	else if (getdown()) {
		setup(true);
		setdown(false);
	}
	else {
		if (getright()) {
			setright(false);
			setleft(true);
		}
		else if (getleft()) {
			setright(true);
			setleft(false);
		}
		else {

			float ran1 = rand() % 10 / 10.0;
			float ran2 = rand() % 10 / 10.0;

			if (ran1 < 0.5) {
				setup(true);
			}
			else {
				setdown(true);
			}

			if (ran2 < 0.5) {
				setright(true);
			}
			else {
				setleft(true);
			}
		}
	}
}

bool Monster::isNotMove(const Point& lastPoint, const Point& curPoint) {
	static int icount = 0;
	++icount;

	int R = 2;
	Rect rect = Rect(
		lastPoint.x - R / 2, lastPoint.y - R / 2,
		R, R
	);

	if (rect.containsPoint(curPoint))
		if (icount > 10) {
			icount = 0;
			return true;
		}
		else
			++icount;

	return false;
}

void Monster::unattack() {
	switch (_weaponTag) {
	case GUN_TAG:
		dynamic_cast<Gun*>(_weapon)->shootController->setIsShot(false);
		break;
	case DAO_TAG:
		dynamic_cast<Knife*>(_weapon)->hitController->setIsHit(false);
		break;
	}
}