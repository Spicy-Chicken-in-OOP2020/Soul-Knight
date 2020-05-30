#include "ShootController.h"
#include "Hero.h"
#include "SafeRoomScene.h"
#include "Entity.h"
#include "Monster.h"

bool ShootController::init()
{
	//��ʼ��״̬
	isShot = false;
	registeKeyBoardEvent();

	this->schedule(schedule_selector(ShootController::bulletUpdate), 0.5f);

	//��ʼ���ӵ�
	Bullet* bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		/*Ӣ���ӵ�*/
		bullet->setTag(HERO_BULLET);
		bulletList[i] = bullet;
		//�����Ӳ���
		//this->addChild(bullet); 
		//ֱ�ӽ��ӵ����볡����

		GlobalParameter::mapNow->getParent()->addChild(bullet, 11);

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
		auto entity = this->getParent()->getParent();
		auto p1 = dynamic_cast<Hero*>(entity);
		auto p2 = dynamic_cast<Monster*>(entity);

		//���ӵ����б�������ÿ�ʹ�õ��ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//���ÿɼ���
				bulletList[i]->setActive(true);
				//��ʼ����λ��
				//Point shootPosition = hero->getPosition();
				Point shootPosition;
				if (p1)
					shootPosition = p1->getPosition();
				else
					shootPosition = p2->getPosition();
				/*
				Point posLyaer = hero->getParent()->getPosition();
				shootPosition.x += posLyaer.x;
				shootPosition.y += posLyaer.y;*/
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


ShootController* ShootController::createForMonster() {
	auto shootController = new ShootController();
	if (shootController && shootController->initForMonsters()) {
		shootController->retain();
	}
	else {
		CC_SAFE_DELETE(shootController);
	}

	return shootController;
}

bool ShootController::initForMonsters() {
	isShot = false;

	//��ʼ���ӵ�
	Bullet* bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		/*�����ӵ�*/
		bullet->setTag(MONSTER_BULLET);
		bulletList[i] = bullet;

		//ֱ�ӽ��ӵ����볡����
		GlobalParameter::mapNow->getParent()->addChild(bullet, 11);
	}

	this->schedule(schedule_selector(ShootController::bulletUpdateMonster), 2.0f);

	return true;
}

void ShootController::setIsShot(bool isShot) {
	this->isShot = isShot;
}

void ShootController::bulletUpdateMonster(float dt)
{
	if (isShot)
	{
		//��ȡ�����ǵ�����λ��
		auto entity = this->getParent()->getParent();
		auto p1 = dynamic_cast<Hero*>(entity);
		auto p2 = dynamic_cast<Monster*>(entity);

		//���ӵ����б�������ÿ�ʹ�õ��ӵ�
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//���ÿɼ���
				bulletList[i]->setActive(true);
				//��ʼ����λ��
				//Point shootPosition = hero->getPosition();
				Point shootPosition;
				if (p1)
					shootPosition = p1->getPosition();
				else
					shootPosition = p2->getPosition();


				if (dynamic_cast<Monster*>(this->getParent()->getParent())->getright())
				{
					if (dynamic_cast<Monster*>(this->getParent()->getParent())->getup())
					{
						//����
						shootPosition.x += 45;
						shootPosition.y += 15;
					}
					else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getdown())
					{
						//����
						shootPosition.x += 55;
						shootPosition.y -= 45;
					}
					else
					{
						//������
						shootPosition.x += 55;
						
					}
				}
				else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getleft())
				{
					if (dynamic_cast<Monster*>(this->getParent()->getParent())->getup())
					{
						//����
						shootPosition.x -= 45;
						shootPosition.y += 15;
					}
					else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getdown())
					{
						//����
						shootPosition.x -= 55;
						shootPosition.y -= 45;
					}
					else
					{
						//������
						shootPosition.x -= 55;
						
					}
				}

				//ִ���������
				bulletList[i]->shootForMonster(shootPosition, dynamic_cast<Monster*>(this->getParent()->getParent()));
				//�����Ч
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BulletShoot.mp3");
				break;
			}
		}


	}
}