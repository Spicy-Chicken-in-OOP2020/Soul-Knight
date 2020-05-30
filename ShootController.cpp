#include "ShootController.h"
#include "Hero.h"
#include "SafeRoomScene.h"
#include "Entity.h"
#include "Monster.h"

bool ShootController::init()
{
	//初始化状态
	isShot = false;
	registeKeyBoardEvent();

	this->schedule(schedule_selector(ShootController::bulletUpdate), 0.5f);

	//初始化子弹
	Bullet* bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		/*英雄子弹*/
		bullet->setTag(HERO_BULLET);
		bulletList[i] = bullet;
		//加入子层中
		//this->addChild(bullet); 
		//直接将子弹加入场景中

		GlobalParameter::mapNow->getParent()->addChild(bullet, 11);

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
		auto entity = this->getParent()->getParent();
		auto p1 = dynamic_cast<Hero*>(entity);
		auto p2 = dynamic_cast<Monster*>(entity);

		//对子弹进行遍历，获得可使用的子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//设置可见性
				bulletList[i]->setActive(true);
				//初始发射位置
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
				//为了让子弹与枪支口重叠的位置修正
				if (GlobalParameter::rightSide)
				{
					if (GlobalParameter::upSide)
					{
						//右上
						shootPosition.x += 45;
						shootPosition.y += 15;
					}
					else if (GlobalParameter::downSide)
					{
						//右下
						shootPosition.x += 55;
						shootPosition.y -= 45;
					}
					else
					{
						//仅朝右
						shootPosition.x += 55;
						shootPosition.y -= 15;
					}
				}
				else if (GlobalParameter::leftSide)
				{
					if (GlobalParameter::upSide)
					{
						//左上
						shootPosition.x -= 45;
						shootPosition.y += 15;
					}
					else if (GlobalParameter::downSide)
					{
						//左下
						shootPosition.x -= 55;
						shootPosition.y -= 45;
					}
					else
					{
						//仅朝左
						shootPosition.x -= 55;
						shootPosition.y -= 15;
					}
				}
				else
				{
					if (GlobalParameter::upSide)
					{
						//仅朝上
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
						//仅朝下
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
				//执行射击动作
				bulletList[i]->shoot(shootPosition);
				//射击音效
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

	//初始化子弹
	Bullet* bullet = NULL;
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet = new Bullet;
		/*怪物子弹*/
		bullet->setTag(MONSTER_BULLET);
		bulletList[i] = bullet;

		//直接将子弹加入场景中
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
		//获取到主角的坐标位置
		auto entity = this->getParent()->getParent();
		auto p1 = dynamic_cast<Hero*>(entity);
		auto p2 = dynamic_cast<Monster*>(entity);

		//对子弹进行遍历，获得可使用的子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//设置可见性
				bulletList[i]->setActive(true);
				//初始发射位置
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
						//右上
						shootPosition.x += 45;
						shootPosition.y += 15;
					}
					else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getdown())
					{
						//右下
						shootPosition.x += 55;
						shootPosition.y -= 45;
					}
					else
					{
						//仅朝右
						shootPosition.x += 55;
						
					}
				}
				else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getleft())
				{
					if (dynamic_cast<Monster*>(this->getParent()->getParent())->getup())
					{
						//左上
						shootPosition.x -= 45;
						shootPosition.y += 15;
					}
					else if (dynamic_cast<Monster*>(this->getParent()->getParent())->getdown())
					{
						//左下
						shootPosition.x -= 55;
						shootPosition.y -= 45;
					}
					else
					{
						//仅朝左
						shootPosition.x -= 55;
						
					}
				}

				//执行射击动作
				bulletList[i]->shootForMonster(shootPosition, dynamic_cast<Monster*>(this->getParent()->getParent()));
				//射击音效
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BulletShoot.mp3");
				break;
			}
		}


	}
}