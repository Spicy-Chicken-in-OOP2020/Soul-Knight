#include "SafeRoomScene.h"
#include "Hero.h"
#include "MoveController.h"
#include "ShootController.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "MonsterManager.h"
#include "PauseLayer1.h"
#include "Items.h"
#include "GlobalParameter.h"
#include "Gun.h"
#include "HitController.h"
#include "Knife.h"
#include "QuickGun.h"

USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;

TMXTiledMap* SafeRoomScene::_safeRoomMap = nullptr;

MonsterManager* SafeRoomScene::_monsterManager = nullptr;

PauseLayer* SafeRoomScene::_pauseLayer = nullptr;

SafeRoomScene* SafeRoomScene::_safeRoomScene = nullptr;

Hero* SafeRoomScene::_hero = nullptr;

Scene* SafeRoomScene::createScene() {
	/*创建场景*/
	if (_safeRoomScene != nullptr)
		return _safeRoomScene;

	_safeRoomScene = SafeRoomScene::create();
	
	_safeRoomScene->retain();
	
	
	/*添加地图*/
	_safeRoomScene->addMap();

	/*左上角*/
	auto layer = _safeRoomScene->mainUiInit(_safeRoomScene->_hero);
	_safeRoomScene->addChild(layer,2);

	

	/*暂停界面*/
	_pauseLayer = PauseLayer::createPauseLayer();
	_pauseLayer->setVisible(false);
	_safeRoomScene->addChild(_pauseLayer, 3);

	
	
	return _safeRoomScene;
}

bool SafeRoomScene::init() {
	if (!Scene::init()) {
		return false;
	}
	return true;
}

void SafeRoomScene::addMap() {
	auto layer = Layer::create();
	_safeRoomScene->addChild(layer, 1);
	_hero = nullptr;
	_safeRoomMap = TMXTiledMap::create("soul_knight_1_3.tmx");
	//设定当前所在地图
	GlobalParameter::mapNow = _safeRoomMap;
	layer->addChild(_safeRoomMap,1);
	//add hero
	_hero =addHero(_safeRoomMap, layer);

	//test monster
	_monsterManager = MonsterManager::createMonsterManagerWithLevel(1);
	layer->addChild(_monsterManager,3);

	Items* item = Items::createItems(BAOXIANG_TAG, _hero->getPosition());
	layer->addChild(item, 2);
}

Hero* SafeRoomScene::addHero(TMXTiledMap* map, Layer* layer) {


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("KnightImage.png");

	_hero = Hero::create(playerSprite);
	_hero->setPosition(Point(100, visibleSize.height / 2));
	layer->addChild(_hero,4);

	_hero->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();


	_hero->setController(move);

	//添加主角初始武器
	/*
	ShootController* shoot = ShootController::create();
	Gun* gun = new Gun(shoot, 3, "普通的枪支");
	_hero->setWeapon(gun);*/
	/*HitController* hitContro = HitController::create();
	Knife* knife = new Knife(hitContro, 3, "匕首");
	_hero->setWeapon(knife);*/
	QuickGun* quickGun = new QuickGun(3, "冲锋枪");
	_hero->setWeapon(quickGun);



	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroStart");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	_hero->setPosition(Point(heroX, heroY));

	//TMXObjectGroup* monsterStartPointGroup = SafeRoomScene::_safeRoomMap->getObjectGroup("monster_1");
	//ValueMap monsterStartPoint;
	//monsterStartPoint = monsterStartPointGroup->getObject(StringUtils::format("monster%d", 1));

	//	/*monster起始点*/
	//	float X = monsterStartPoint.at("x").asFloat();
	//	float Y = monsterStartPoint.at("y").asFloat();

	//	_hero->setPosition(X, Y);

	Items* item = Items::createItems(GUN_TAG, _hero->getPosition());

	layer->addChild(item, 2);


	//世界主角
	GlobalParameter::hero = _hero;
	
	return _hero;
}

void SafeRoomScene::pauseButton(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED: {
		_pauseLayer->setVisible(true);
		break;
	}
	}
}

Layer* SafeRoomScene::mainUiInit(Hero* hero){
	auto layer = Layer::create();
	auto mainUI = GUIReader::getInstance()->widgetFromJsonFile("MainUI.ExportJson");
	layer->addChild(mainUI);
	Button* stopButton = (Button*)Helper::seekWidgetByName(mainUI, "StopButton");

	/*暂停界面调取*/
	stopButton->addTouchEventListener(stopButton, toucheventselector(SafeRoomScene::pauseButton));

	//获取主角HP,护甲,MP
	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	auto playerHpLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayHpNow");
	auto playerHpMaxLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayHpMax");
	hero->bindHp(playerHpUI, playerHpLabel, playerHpMaxLabel);
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI_0");
	auto playerDefendenseLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayDefendenseNow");
	auto playerDefendenseMaxLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayDefendenseMax");
	hero->bindDefense(playerDefendenseUI, playerDefendenseLabel, playerDefendenseMaxLabel);
	auto playerMpUI = static_cast<LoadingBar*>(Helper::seekWidgetByName(mainUI, "PlayerMpUI"));
	auto playerMpLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayMpNow");
	auto playerMpMaxLabel = (Text*)Helper::seekWidgetByName(mainUI, "BoundarayMpMax");
	hero->bindMp(playerMpUI, playerMpLabel, playerMpMaxLabel);

	return layer;
}


