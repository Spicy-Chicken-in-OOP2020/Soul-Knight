#include "GateRoomScene.h"
#include "GlobalParameter.h"
#include "SafeRoomScene.h"
#include "MoveController.h"
#include "ShootController.h"
//
//int GateRoomScene::curNum = 0;
//int GateRoomScene::curGate = 0;
//PauseLayer* GateRoomScene::_pauseLayer = nullptr;

Scene* GateRoomScene::createScene() {
	auto scene = Scene::create();
	auto layer1 = GateRoomScene::create();


//	_pauseLayer = PauseLayer::createPauseLayer();
//	_pauseLayer->setVisible(false);

	scene->addChild(layer1, 1);
//	scene->addChild(_pauseLayer, 3);

	return scene;

}
bool GateRoomScene::init() {
	if (!Layer::init()) {
		return false;
	}
	GlobalParameter::mapNow = TMXTiledMap::create("soul_knight_1_3.tmx");
	
	this->bindCurGateRoomMap(GlobalParameter::mapNow);
	this->addChild(curGateRoomMap);

	/*this->bindHero(addHero(GlobalParameter::mapNow));*/
	//GlobalParameter::hero = _hero;
	//this->bindCurGateRoomMap(GlobalParameter::mapNow);
	//this->bindPortal();
	////应该是加载当前的地图界面; 需要改进 每次地图都在改变的;
	//registeKeyBoardEvent();
	return true;
}

void GateRoomScene::bindCurGateRoomMap(TMXTiledMap* map) {
	this->curGateRoomMap = map;
}
//void GateRoomScene::registeKeyBoardEvent() {
//	auto keyBoardListener = EventListenerKeyboard::create();
//	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
//		switch (keyCode) {
//		case EventKeyboard::KeyCode::KEY_Z: //攻击键Z;
//			if (canBeTransmitted()) {
//				if (curNum == 0) { //为了关卡的地图的移动;
//					curNum++;    //还需要Boss地图的传送门处理;
//					curGate++;
//				}
//				else {
//					curNum = curGate == 5 ? curNum : curNum + 1;
//					curGate = (curGate + 1) % 6;
//
//				}
//				//Director::getInstance()->replaceScene(GateRoomScene::createScene(_hero,
//				//	TMXTiledMap::create(StringUtils::format(".\\soul_knight%d_%d\\soul_knight_%d_%d.tmx", curNum, curGate, curNum, curNum))));
//				Director::getInstance()->replaceScene(SafeRoomScene::createScene());
//			}
//			else {
//				break;
//			}
//			//判断人物位置是否在传送门矩形内; //也可以通过攻击按键来判断是否可以与npc通话;
//			//else if(//判断是否有NPC进行展开操作);
//		case EventKeyboard::KeyCode::KEY_Q: //场景中可以通过Q按键 暂停;
//			_pauseLayer->setVisible(true);
//
//			//case EventKeyboard::KeyCode 场景中可以通过A按键切换自己的武器;
//		//case EventKeyboard::KeyCode 场景中可以通过Q按键 暂停;
//		/*
//		case EventKeyboard::KeyCode::KEY_Q:
//			//pauseGame(); 游戏暂停键的调用;
//		//case EventKeyboard::KeyCode 场景中可以通过S按键切换自己的武器;
//		case EventKeyboard::KeyCode::KEY_S:
//			//_hero->switchWeapons(); //可以调用Hero的调换武器函数;
//		case EventKeyboard::KeyCode::KEY_D:
//			//_hero->battleSkill(); //使用_hero的特殊技能;
//		}
//		*/
//		};
//	};
//	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
//
//	};
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
//}
//
//Point GateRoomScene::getHeroPos() {
//	return this->_hero->getPosition();
//}
//
//bool GateRoomScene::canBeTransmitted() {
//	Point heroPos = getHeroPos();
//	
//	CCTMXObjectGroup* objects = this->curGateRoomMap->objectGroupNamed("hero");
//	ValueMap portalPos = objects->getObject("portal");
//	
//
//	float x = portalPos.at("x").asFloat();
//	float y = portalPos.at("y").asFloat();
//	float portalWidth = portalPos.at("width").asFloat();
//	float portalHeight = portalPos.at("height").asFloat();
//	Rect portalRec(x,y,portalWidth,portalHeight);
//
//	if (portalRec.containsPoint(heroPos)){
//		return true;
//	}
//	return false;
//}
//
//
///*Point GateRoomScene::tileCoordForPosition(Point pos) {
//	Size mapSize = curGateRoomMap->getMapSize();
//	Size tileSize =curGateRoomMap->getTileSize();
//
//	int x = pos.x / tileSize.width;
//
//	int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
//
//	return Point(x, y);
//}*/
//
//void GateRoomScene::bindHero(Hero* hero) {
//	_hero = hero;
//}
//
//Hero* GateRoomScene::addHero(TMXTiledMap* map) {
//
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//	//创建一个hero，加入到场景中;
//	Sprite* playerSprite = Sprite::create(".\\picture\\Knight1.png");
//
//	Hero* mPlayer = Hero::create(playerSprite);
//	mPlayer->setPosition(Point(100, visibleSize.height / 2));
//	this->addChild(mPlayer);
//
//	mPlayer->setSafeRoomTiledMap(map);
//
//	//为hero添加一个移动控制器;
//	MoveController* move = MoveController::create();
//	//为 hero添加一个射击控制器;
//	ShootController* shoot = ShootController::create();
//	this->addChild(move);
//
//	mPlayer->setController(move, shoot);
//
//	//利用地图的对象层初始主角的出生地;
//	TMXObjectGroup* heroGroup = map->getObjectGroup("hero");
//	ValueMap heroPointMap = heroGroup->getObject("heroStart");
//
//
//	float heroX = heroPointMap.at("x").asFloat();
//	float heroY = heroPointMap.at("y").asFloat();
//	mPlayer->setPosition(Point(heroX, heroY));
//
//	return mPlayer;
//}
//void GateRoomScene::bindPortal() {
//	Sprite* sprite = Sprite::create(".\\picture\\portal.png");
//	TMXObjectGroup* heroGroup = GlobalParameter::mapNow->getObjectGroup("hero");
//	ValueMap heroPointMap = heroGroup->getObject("portal");
//
//
//	float portalX = heroPointMap.at("x").asFloat();
//	float portalY = heroPointMap.at("y").asFloat();
//
//	sprite->setPosition(Point(portalX, portalY));
//
//	this->addChild(sprite);
//}