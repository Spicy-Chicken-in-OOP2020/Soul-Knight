#include "MoveController.h"
#include "Hero.h"

bool MoveController::init() {
	/*init时,设置各个方向位移为0*/
	this->upSpeed = 0;
	this->leftSpeed = 0;
	this->rightSpeed = 0;
	this->downSpeed = 0;

	registeKeyBoardEvent();
	
	this->scheduleUpdate();
	
	return true;
}

void MoveController::update(float dt) {
	if (MyControlListener == NULL) {
		return;
	}
	
	//计算新的坐标值
	Point curPos = MyControlListener->getTagPosition();
	curPos.x += rightSpeed - leftSpeed;
	curPos.y += upSpeed - downSpeed;

	//更改坐标
	if (!MyControlListener->setTagPosition(curPos.x,curPos.y))
	{
		//后撤一定距离
		log("You walked into a bad way.");

	}

	//在这里更新主角武器样式
	
}

void MoveController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW: //上方向键;
			setUpSpeed(3);
			GlobalParameter::downSide = false;
			GlobalParameter::upSide = true;
			if (getLeftSpeed() == 0 && getRightSpeed() == 0)
			{
				GlobalParameter::rightSide = false;
				GlobalParameter::leftSide = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setDownSpeed(3);
			GlobalParameter::upSide = false;
			GlobalParameter::downSide = true;
			if (getLeftSpeed() == 0 && getRightSpeed() == 0)
			{
				GlobalParameter::rightSide = false;
				GlobalParameter::leftSide = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setLeftSpeed(3);
			GlobalParameter::rightSide = false;
			GlobalParameter::leftSide = true;
			GlobalParameter::upSide = false;
			GlobalParameter::downSide = false;
			GlobalParameter::hero->setHeroRun(false);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(3);
			GlobalParameter::leftSide = false;
			GlobalParameter::rightSide = true;
			GlobalParameter::upSide = false;
			GlobalParameter::downSide = false;
			GlobalParameter::hero->setHeroRun(true);
			break;
			
		}
	};

	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			setUpSpeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setDownSpeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setLeftSpeed(0);
			GlobalParameter::hero->setHeroStill(false);
			GlobalParameter::imageLeftSide = true;
			GlobalParameter::imageRightSide = false;
			if (getRightSpeed() != 0)
				GlobalParameter::hero->setHeroRun(true);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(0);
			GlobalParameter::hero->setHeroStill(true);
			GlobalParameter::imageLeftSide = false;
			GlobalParameter::imageRightSide = true;
			if (getLeftSpeed() != 0)
				GlobalParameter::hero->setHeroRun(false);
			break;
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}