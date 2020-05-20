#include "MoveController.h"


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

}

void MoveController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW: //上方向键;
			setUpSpeed(3);
			GlobalParameter::downSide = false;
			GlobalParameter::upSide = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setDownSpeed(3);
			GlobalParameter::upSide = false;
			GlobalParameter::downSide = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setLeftSpeed(3);
			GlobalParameter::rightSide = false;
			GlobalParameter::leftSide = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(3);
			GlobalParameter::leftSide = false;
			GlobalParameter::rightSide = true;
			break;
			
		}
	};
	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			setUpSpeed(0);
			if (getLeftSpeed() + getRightSpeed() == 0)
			{
				GlobalParameter::leftSide = false;
				GlobalParameter::rightSide = false;
			}
			else
			{
				GlobalParameter::downSide = false;
				GlobalParameter::upSide = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setDownSpeed(0);
			if (getLeftSpeed() + getRightSpeed() == 0)
			{
				GlobalParameter::leftSide = false;
				GlobalParameter::rightSide = false;
			}
			else
			{
				GlobalParameter::downSide = false;
				GlobalParameter::upSide = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setLeftSpeed(0);
			if (getUpSpeed() + getDownSpeed() == 0)
			{
				GlobalParameter::upSide = false;
				GlobalParameter::downSide = false;
			}
			else
			{
				GlobalParameter::leftSide = false;
				GlobalParameter::rightSide = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(0);
			if (getUpSpeed() + getDownSpeed() == 0)
			{
				GlobalParameter::upSide = false;
				GlobalParameter::downSide = false;
			}
			else
			{
				GlobalParameter::leftSide = false;
				GlobalParameter::rightSide = false;
			}
			break;
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}