#include "SafeRoomScene.h"
#include "Hero.h"
#include "MoveController.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;


Scene* SafeRoomScene::createScene() {
	auto scene = Scene::create();
	auto layer = SafeRoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool SafeRoomScene::init() {
	if (!Scene::init()) {
		return false;
	}
	TMXTiledMap* safeRoomMap = TMXTiledMap::create("MainMap.tmx");
	this->addChild(safeRoomMap);
	Hero* hero=addHero(safeRoomMap);

	auto layer = Layer::create();
	auto mainUI = GUIReader::getInstance()->widgetFromJsonFile("MainUI.ExportJson");
	layer->addChild(mainUI);
	this->addChild(layer);
	
	//获取按钮事件
	Button* stopButton = (Button*)Helper::seekWidgetByName(mainUI, "stopButton");

	//获取主角HP,护甲,MP

	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	auto playerHpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHp");
	auto playerHpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpMax");
	hero->bindHp(playerHpUI,playerHpLabel,playerHpMaxLabel);
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	auto playerDefendenseLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendense");
	auto playerDefendenseMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseMax");
	hero->bindDefense(playerDefendenseUI, playerDefendenseLabel, playerDefendenseMaxLabel);
	auto playerMpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerMpUI");
	auto playerMpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMp");
	auto playerMpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpMax");
	hero->bindHp(playerMpUI, playerMpLabel, playerMpMaxLabel);

	return true;
}
Hero* SafeRoomScene::addHero(TMXTiledMap* map) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("Knight1.png");

	Hero* mPlayer = Hero::create(playerSprite);
	mPlayer->setPosition(Point(100, visibleSize.height / 2));
	this->addChild(mPlayer);

	mPlayer->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();
	this->addChild(move);
	mPlayer->setController(move);

	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroDir");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	mPlayer->setPosition(Point(heroX, heroY));

	return mPlayer;
}
