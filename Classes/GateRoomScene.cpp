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
	////Ӧ���Ǽ��ص�ǰ�ĵ�ͼ����; ��Ҫ�Ľ� ÿ�ε�ͼ���ڸı��;
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
//		case EventKeyboard::KeyCode::KEY_Z: //������Z;
//			if (canBeTransmitted()) {
//				if (curNum == 0) { //Ϊ�˹ؿ��ĵ�ͼ���ƶ�;
//					curNum++;    //����ҪBoss��ͼ�Ĵ����Ŵ���;
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
//			//�ж�����λ���Ƿ��ڴ����ž�����; //Ҳ����ͨ�������������ж��Ƿ������npcͨ��;
//			//else if(//�ж��Ƿ���NPC����չ������);
//		case EventKeyboard::KeyCode::KEY_Q: //�����п���ͨ��Q���� ��ͣ;
//			_pauseLayer->setVisible(true);
//
//			//case EventKeyboard::KeyCode �����п���ͨ��A�����л��Լ�������;
//		//case EventKeyboard::KeyCode �����п���ͨ��Q���� ��ͣ;
//		/*
//		case EventKeyboard::KeyCode::KEY_Q:
//			//pauseGame(); ��Ϸ��ͣ���ĵ���;
//		//case EventKeyboard::KeyCode �����п���ͨ��S�����л��Լ�������;
//		case EventKeyboard::KeyCode::KEY_S:
//			//_hero->switchWeapons(); //���Ե���Hero�ĵ�����������;
//		case EventKeyboard::KeyCode::KEY_D:
//			//_hero->battleSkill(); //ʹ��_hero�����⼼��;
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
//	//����һ��hero�����뵽������;
//	Sprite* playerSprite = Sprite::create(".\\picture\\Knight1.png");
//
//	Hero* mPlayer = Hero::create(playerSprite);
//	mPlayer->setPosition(Point(100, visibleSize.height / 2));
//	this->addChild(mPlayer);
//
//	mPlayer->setSafeRoomTiledMap(map);
//
//	//Ϊhero���һ���ƶ�������;
//	MoveController* move = MoveController::create();
//	//Ϊ hero���һ�����������;
//	ShootController* shoot = ShootController::create();
//	this->addChild(move);
//
//	mPlayer->setController(move, shoot);
//
//	//���õ�ͼ�Ķ�����ʼ���ǵĳ�����;
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