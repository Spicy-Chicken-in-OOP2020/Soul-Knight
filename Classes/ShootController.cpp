#include "ShootController.h"

bool ShootController::init()
{
	isShot = false;
	this->scheduleUpdate();

	//��ʼ���ӵ�
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
		case EventKeyboard::KeyCode::KEY_J: //�����
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
		//������Ҫ��ȡ�����ǵ�����λ��
		auto hero = (Hero*)this->getParent();
		auto moveController = (MoveController*)hero->getMoveController();

		//���ӵ����е�һ�ֱ����������ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (bulletList[i]->isActive&&bulletList[i]->isArrive())
			{
				bulletList[i]->setActive(false);
			}
		}

		//���ӵ����еڶ��ֱ����������δʹ�ù����ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (bulletList[i]->isActive == false)
			{
				bulletList[i]->setActive(true);
				
				//���ݵ�ǰMoveController�����ȷ���������
				bulletList[i]->upSpeed = moveController->getUpSpeed();
				bulletList[i]->downSpeed = moveController->getDownSpeed();
				bulletList[i]->leftSpeed = moveController->getLeftSpeed();
				bulletList[i]->rightSpeed = moveController->getRightSpeed();

				//ִ���������
				bulletList[i]->shoot(hero->getTagPosition());

				break;
			}
		}

		
	}
}