#include "SafeRoomScene.h"
#include "Hero.h"
#include "MoveController.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;

Scene* SafeRoomScene::createScene() {
	/*创建物理世界的场景*/
	auto scene = Scene::create();

	auto layer1 = SafeRoomScene::create();
	layer1->onEnter();
	scene->addChild(layer1);

	auto layer2 = layer1->mainUiInit(layer1->_hero);
	scene->addChild(layer2);

	return scene;
}

bool SafeRoomScene::init() {
	if (!Layer::init()) {
		return false;
	}
	_hero = nullptr;
	TMXTiledMap* safeRoomMap = TMXTiledMap::create("MainMap.tmx");
	//设定当前所在地图
	GlobalParameter::mapNow = safeRoomMap;
	this->addChild(safeRoomMap);
	//add hero
	_hero = addHero(safeRoomMap);

	

	Monster* monster = nullptr;
	//test monster
	//MonsterManager* monsterManager = MonsterManager::createMonsterManagerWithLevel(1);
	//_monsterManager = monsterManager;
	//this->addChild(_monsterManager);


	//读取地刺层
	TMXObjectGroup* spikeGroup = GlobalParameter::mapNow->getObjectGroup("spikeWeed");
	//获取所有地刺
	ValueMap spikePointVec;

	int spikeNum = 0;

	//当可以继续读取时
	while ((spikePointVec = spikeGroup->getObject(StringUtils::format("spikeWeed%d", spikeNum + 1))).size())
	{
		log("A spikeWeed is loading!");
		spikeNum++;

		//在该位置放置地刺
		float spikeX = spikePointVec.at("x").asFloat();
		float spikeY = spikePointVec.at("y").asFloat();

		//生成一个新的地刺
		SpikeWeed* spikeweed = new SpikeWeed();
		spikeweed->setPosition(Point(spikeX, spikeY));
		spikeList.pushBack(spikeweed);
		GlobalParameter::mapNow->getParent()->addChild(spikeweed);
	}
	

	return true;
}

Hero* SafeRoomScene::addHero(TMXTiledMap* map) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("KnightImage.png");

	Hero* mPlayer = Hero::create(playerSprite);
	mPlayer->setPosition(Point(100, visibleSize.height / 2));
	this->addChild(mPlayer);

	mPlayer->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();
	ShootController* shoot = ShootController::create();
	

	mPlayer->setController(move);

	//添加主角初始武器
	Gun* gun = new Gun(shoot, 3, "普通的枪支");
	mPlayer->setWeapon(gun);
	
	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroDir");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	mPlayer->setPosition(Point(heroX, heroY));

	//世界主角
	GlobalParameter::hero = mPlayer;

	return mPlayer;
}

Layer* SafeRoomScene::mainUiInit(Hero* hero) {
	auto layer = Layer::create();
	auto mainUI = GUIReader::getInstance()->widgetFromJsonFile("MainUI.ExportJson");
	layer->addChild(mainUI);
	Button* stopButton = (Button*)Helper::seekWidgetByName(mainUI, "stopButton");

	//获取主角HP,护甲,MP
	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	auto playerHpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayHpNow");
	auto playerHpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayHpMax");
	hero->bindHp(playerHpUI, playerHpLabel, playerHpMaxLabel);
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	auto playerDefendenseLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayDefendenseNow");
	auto playerDefendenseMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayDefendenseMax");
	hero->bindDefense(playerDefendenseUI, playerDefendenseLabel, playerDefendenseMaxLabel);
	auto playerMpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerMpUI");
	auto playerMpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayMpNow");
	auto playerMpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundarayMpMax");
	hero->bindHp(playerMpUI, playerMpLabel, playerMpMaxLabel);

	//设定初值，为了UI和数值的统一
	hero->setHp(hero->gethp());
	hero->sethpMax(hero->gethpMax());
	hero->setMp(hero->getmp());
	hero->setMpMax(hero->getmpMax());
	hero->setDefense(hero->getdefense());
	hero->setDefenseMax(hero->getdefenseMax());

	return layer;
}
