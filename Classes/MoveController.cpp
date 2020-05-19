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
	Point curPos = MyControlListener->getTagPosition();
	curPos.x += rightSpeed - leftSpeed;
	curPos.y += upSpeed - downSpeed;
	MyControlListener->setTagPosition(curPos.x, curPos.y);

}
void MoveController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW: //上方向键;
			setUpSpeed(3);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			setDownSpeed(3);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setLeftSpeed(3);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(3);
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
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRightSpeed(0);
			break;
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}