#include "TollgateScene.h"
#include "TollGateMapLayer.h"
#include "MoveController.h"
Scene* TollgateScene::createScene() {
	auto tollgateScene = TollgateScene::create();
	tollgateScene->retain();
	
	return tollgateScene;
}

bool TollgateScene::init() {
	if (!Scene::init()) {
		return false;
	}

	this->addMap();

	return true;
}

void TollgateScene::addMap() {
	auto path = StringUtils::format(MAP, 1, 1, 1, 1);
	_tollgateMap = TMXTiledMap::create(path);
	_tollgateMap->setPosition(-1000, -500);

	auto layer = Layer::create();
	layer->addChild(_tollgateMap,1);
	this->addChild(layer, 1);
}

Hero* TollgateScene::addHero(TMXTiledMap* map, Layer* layer) {


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("KnightImage.png");

	_hero = Hero::create(playerSprite);
	_hero->setPosition(Point(100, visibleSize.height / 2));
	layer->addChild(_hero, 3);

	_hero->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();



	_hero->setController(move);

	//添加主角初始武器
	/*
	ShootController* shoot = ShootController::create();
	Gun* gun = new Gun(shoot, 3, "普通的枪支");
	_hero->setWeapon(gun);*/
	HitController* hitContro = HitController::create();
	Knife* knife = new Knife(hitContro, 3, "匕首");
	_hero->setWeapon(knife);


	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroDir");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	_hero->setPosition(Point(heroX, heroY));

	//世界主角
	GlobalParameter::hero = _hero;

	return _hero;
}