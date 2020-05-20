#include "ShootController.h"

bool ShootController::init()
{
	//初始化状态
	isShot = false;
	registeKeyBoardEvent();

	this->schedule(schedule_selector(ShootController::bulletUpdate), 0.5f);

	//初始化子弹
	Bullet*bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		bulletList[i] = bullet;
		//加入子层中
		//this->addChild(bullet);  
		GlobalParameter::mapNow->getParent()->addChild(bullet);
	}

	return true;
}

void ShootController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J://射击键
			log("Shoot is open!");
			isShot = true;
			break;
		}
	};
	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J:
			isShot = false;
			//this->unschedule();
			break;

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}

void ShootController::bulletUpdate(float dt)
{
	if (isShot)
	{
		//获取到主角的坐标位置
		auto hero = (Hero*)this->getParent();
		auto moveController = (MoveController*)hero->getMoveController();

		//对子弹进行遍历，获得可使用的子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//设置可见性
				bulletList[i]->setActive(true);
				//执行射击动作
				bulletList[i]->shoot(hero->getPosition());
				//射击音效
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BulletShoot.mp3");
				break;
			}
		}

		
	}
}