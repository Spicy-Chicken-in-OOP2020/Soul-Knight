#include "SafeRoomScene.h"
#include "Hero.h"
#include "MoveController.h"
#include "ShootController.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "MonsterManager.h"
#include "PauseLayer1.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;
MonsterManager* SafeRoomScene::_monsterManager = nullptr;

PauseLayer* SafeRoomScene::_pauseLayer = nullptr;

SafeRoomScene* SafeRoomScene::_safeRoomScene = nullptr;

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
	_hero = nullptr;
	TMXTiledMap* safeRoomMap = TMXTiledMap::create("MainMap.tmx");
	//设定当前所在地图
	GlobalParameter::mapNow = safeRoomMap;
	layer->addChild(safeRoomMap);
	//add hero
	_hero =addHero(safeRoomMap, layer);

	//test monster
	_monsterManager = MonsterManager::createMonsterManagerWithLevel(1);
	layer->addChild(_monsterManager);

	_safeRoomScene->addChild(layer, 1);
}

Hero* SafeRoomScene::addHero(TMXTiledMap* map, Layer* layer) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("Knight1.png");

	Hero* mPlayer = Hero::create(playerSprite);
	mPlayer->setPosition(Point(100, visibleSize.height / 2));
	layer->addChild(mPlayer);

	mPlayer->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();
	ShootController* shoot = ShootController::create();
	layer->addChild(move);
	
	
	mPlayer->setController(move,shoot);

	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroDir");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	mPlayer->setPosition(Point(heroX, heroY));

	return mPlayer;
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
	auto playerHpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHp");
	auto playerHpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpMax");
	hero->bindHp(playerHpUI, playerHpLabel, playerHpMaxLabel);
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	auto playerDefendenseLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendense");
	auto playerDefendenseMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseMax");
	hero->bindDefense(playerDefendenseUI, playerDefendenseLabel, playerDefendenseMaxLabel);
	auto playerMpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerMpUI");
	auto playerMpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMp");
	auto playerMpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpMax");
	hero->bindHp(playerMpUI, playerMpLabel, playerMpMaxLabel);

	return layer;
}
