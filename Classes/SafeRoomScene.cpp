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

USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;
MonsterManager* SafeRoomScene::_monsterManager = nullptr;

PauseLayer* SafeRoomScene::_pauseLayer = nullptr;

SafeRoomScene* SafeRoomScene::_safeRoomScene = nullptr;

Hero* SafeRoomScene::_hero = nullptr;

Scene* SafeRoomScene::createScene() {
	/*��������*/
	if (_safeRoomScene != nullptr)
		return _safeRoomScene;

	_safeRoomScene = SafeRoomScene::create();
	_safeRoomScene->retain();
	
	/*��ӵ�ͼ*/
	_safeRoomScene->addMap();

	/*���Ͻ�*/
	auto layer = _safeRoomScene->mainUiInit(_safeRoomScene->_hero);
	_safeRoomScene->addChild(layer,2);
	

	

	/*��ͣ����*/
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
	_safeRoomMap = TMXTiledMap::create("MainMap.tmx");
	//�趨��ǰ���ڵ�ͼ
	GlobalParameter::mapNow = _safeRoomMap;
	layer->addChild(_safeRoomMap,1);
	//add hero
	_hero =addHero(_safeRoomMap, layer);

	//test monster
	_monsterManager = MonsterManager::createMonsterManagerWithLevel(1);
	layer->addChild(_monsterManager,3);

	//��ȡ�ش̲�
	TMXObjectGroup* spikeGroup = _safeRoomMap->getObjectGroup("spikeWeed");
	//��ȡ���еش�
	ValueMap spikePointVec;

	int spikeNum = 0;

	//�����Լ�����ȡʱ
	while ((spikePointVec = spikeGroup->getObject(StringUtils::format("spikeWeed%d", spikeNum + 1))).size())
	{
		log("A spikeWeed is loading!");
		spikeNum++;

		//�ڸ�λ�÷��õش�
		float spikeX = spikePointVec.at("x").asFloat();
		float spikeY = spikePointVec.at("y").asFloat();

		//����һ���µĵش�
		SpikeWeed* spikeweed = new SpikeWeed();
		spikeweed->setPosition(Point(spikeX, spikeY));
		_spikeList.pushBack(spikeweed);
		layer->addChild(spikeweed,2);
	}

	Items* item = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
	layer->addChild(item, 2);
	
	//_safeRoomScene->addChild(layer, 1);
}

Hero* SafeRoomScene::addHero(TMXTiledMap* map, Layer* layer) {


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* playerSprite = Sprite::create("KnightImage.png");

	_hero = Hero::create(playerSprite);
	_hero->setPosition(Point(100, visibleSize.height / 2));
	layer->addChild(_hero,3);

	_hero->setSafeRoomTiledMap(map);

	MoveController* move = MoveController::create();



	_hero->setController(move);

	//������ǳ�ʼ����
	/*
	ShootController* shoot = ShootController::create();
	Gun* gun = new Gun(shoot, 3, "��ͨ��ǹ֧");
	_hero->setWeapon(gun);*/
	HitController* hitContro = HitController::create();
	Knife* knife = new Knife(hitContro, 3, "ذ��");
	_hero->setWeapon(knife);


	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
	ValueMap heroPointMap = heroGroup->getObject("heroDir");

	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();

	_hero->setPosition(Point(heroX, heroY));

	//��������
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

	/*��ͣ�����ȡ*/
	stopButton->addTouchEventListener(stopButton, toucheventselector(SafeRoomScene::pauseButton));

	//��ȡ����HP,����,MP
	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	auto playerHpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHp");
	auto playerHpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpMax");
	hero->bindHp(playerHpUI, playerHpLabel, playerHpMaxLabel);
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	auto playerDefendenseLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendense");
	auto playerDefendenseMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseMax");
	hero->bindDefense(playerDefendenseUI, playerDefendenseLabel, playerDefendenseMaxLabel);
	auto playerMpUI = static_cast<LoadingBar*>(Helper::seekWidgetByName(mainUI, "PlayerMpUI"));
	auto playerMpLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMp");
	auto playerMpMaxLabel = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpMax");
	hero->bindHp(playerMpUI, playerMpLabel, playerMpMaxLabel);

	return layer;
}
