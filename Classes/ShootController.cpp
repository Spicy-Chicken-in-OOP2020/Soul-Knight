#include "ShootController.h"
#include "Hero.h"
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
		//ֱ�ӽ��ӵ����볡����
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
		auto hero = (Hero*)this->getParent()->getParent();

		//���ӵ����б�������ÿ�ʹ�õ��ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//���ÿɼ���
				bulletList[i]->setActive(true);
				//��ʼ����λ��
				Point shootPosition = hero->getPosition();
				//Ϊ�����ӵ���ǹ֧���ص���λ������
				if (GlobalParameter::rightSide)
				{
					if (GlobalParameter::upSide)
					{
						//����
						shootPosition.x += 45;
						shootPosition.y += 15;
					}
					else if (GlobalParameter::downSide)
					{
						//����
						shootPosition.x += 55;
						shootPosition.y -= 45;
					}
					else
					{
						//������
						shootPosition.x += 55;
						shootPosition.y -= 15;
					}
				}
				else if (GlobalParameter::leftSide)
				{
					if (GlobalParameter::upSide)
					{
						//����
						shootPosition.x -= 45;
						shootPosition.y += 15;
					}
					else if (GlobalParameter::downSide)
					{
						//����
						shootPosition.x -= 55;
						shootPosition.y -= 45;
					}
					else
					{
						//������
						shootPosition.x -= 55;
						shootPosition.y -= 15;
					}
				}
				else
				{
					if (GlobalParameter::upSide)
					{
						//������
						if (GlobalParameter::imageRightSide)
						{
							shootPosition.x += 20;
							shootPosition.y += 25;
						}
						else
						{
							shootPosition.x -= 20;
							shootPosition.y += 25;
						}
					}
					else
					{
						//������
						if (GlobalParameter::imageRightSide)
						{
							shootPosition.x += 20;
							shootPosition.y -= 55;
						}
						else
						{
							shootPosition.x -= 20;
							shootPosition.y -= 55;
						}
					}
				}
				//ִ���������
				bulletList[i]->shoot(shootPosition);
				//�����Ч
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BulletShoot.mp3");
				break;
			}
		}

		
	}
}