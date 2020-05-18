#include "ShootController.h"

bool ShootController::init()
{
	isShot = false;
	this->scheduleUpdate();

	//初始化子弹
	Bullet*bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = Bullet::create();
		bulletList[i] = bullet;
	}

	return true;
}

void ShootController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J: //射击键
			isShot = true;
			break;

		}
	};
	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J_ARROW:
			isShot = false;
			break;

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}

void ShootController::update(float dt)
{
	if (isShot)
	{
		//这里需要获取到主角的坐标位置
		auto hero = (Hero*)this->getParent();
		auto moveController = (MoveController*)hero->getMoveController();

		//对子弹进行第一轮遍历，回收子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (bulletList[i]->isActive&&bulletList[i]->isArrive())
			{
				bulletList[i]->setActive(false);
			}
		}

		//对子弹进行第二轮遍历，获得尚未使用过的子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (bulletList[i]->isActive == false)
			{
				bulletList[i]->setActive(true);
				
				//根据当前MoveController的情况确定射击方向
				bulletList[i]->upSpeed = moveController->getUpSpeed();
				bulletList[i]->downSpeed = moveController->getDownSpeed();
				bulletList[i]->leftSpeed = moveController->getLeftSpeed();
				bulletList[i]->rightSpeed = moveController->getRightSpeed();

				//执行射击动作
				bulletList[i]->shoot(hero->getTagPosition());

				break;
			}
		}

		
	}
}