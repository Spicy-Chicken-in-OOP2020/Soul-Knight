#include "ShootController.h"
#include "Hero.h"
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
		//直接将子弹加入场景中
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
		auto hero = (Hero*)this->getParent()->getParent();

		//对子弹进行遍历，获得可使用的子弹
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (!bulletList[i]->getActive())
			{
				log("%d Bullet is Active!", i);

				//设置可见性
				bulletList[i]->setActive(true);
				//初始发射位置
				Point shootPosition = hero->getPosition();
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