#include "ShootController.h"

bool ShootController::init()
{
	//��ʼ��״̬
	isShot = false;
	registeKeyBoardEvent();

	this->schedule(schedule_selector(ShootController::bulletUpdate), 0.5f);

	//��ʼ���ӵ�
	Bullet*bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		bulletList[i] = bullet;
		//�����Ӳ���
		//this->addChild(bullet);  
		GlobalParameter::mapNow->getParent()->addChild(bullet);
	}

	return true;
}

void ShootController::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J://�����
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
		//��ȡ�����ǵ�����λ��
		auto hero = (Hero*)this->getParent();
		auto moveController = (MoveController*)hero->getMoveController();

		//���ӵ����б�������ÿ�ʹ�õ��ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//���ÿɼ���
				bulletList[i]->setActive(true);
				//ִ���������
				bulletList[i]->shoot(hero->getPosition());
				//�����Ч
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BulletShoot.mp3");
				break;
			}
		}

		
	}
}