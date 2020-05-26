#include "HitController.h"
#include "Hero.h"
bool HitController::init()
{
	//��ʼ��״̬
	registeKeyBoardEvent();

	//���������Ŷ����Ķ����������
	for (int i = 0; i < MAX_IMAGE_SPRITE_NUM; i++)
	{
		Sprite* sprite = Sprite::create("KnightImage.png");
		actionSpriteVec[i] = sprite;
		actionSpriteRun[i] = false;
		GlobalParameter::mapNow->getParent()->addChild(sprite,11);
		sprite->setVisible(false);
	}

	this->schedule(schedule_selector(HitController::hitUpdate), 0.5f);
	this->isHit = false;
	return true;
}

void HitController::registeKeyBoardEvent()
{
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J://�����
			this->isHit = true;
			break;
		}
	};
	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_J:
			this->isHit = false;
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}

void HitController::hitUpdate(float dt)
{
	if (isHit)
	{
		//��spriteVec��ȡ��һ��û�б�ʹ�õ�
		Sprite* actionSprite = nullptr;

		static int index;

		for (index = 0; index < MAX_IMAGE_SPRITE_NUM; index++)
		{
			//��ǰδ����
			if (actionSpriteRun[index] == false)
			{
				actionSprite = actionSpriteVec[index];
				actionSpriteRun[index] = true;
				break;
			}
		}

		Point hitPosition = GlobalParameter::hero->getPosition();
		//���ݵ�ǰλ���趨��ʼ����
		if (GlobalParameter::rightSide)
		{
			if (GlobalParameter::upSide)
			{
				//����
				hitPosition.x += 45;
				hitPosition.y += 15;
			}
			else if (GlobalParameter::downSide)
			{
				//����
				hitPosition.x += 55;
				hitPosition.y -= 45;
			}
			else
			{
				//������
				hitPosition.x += 55;
				hitPosition.y -= 15;
			}
		}
		else if (GlobalParameter::leftSide)
		{
			if (GlobalParameter::upSide)
			{
				//����
				hitPosition.x -= 45;
				hitPosition.y += 15;
			}
			else if (GlobalParameter::downSide)
			{
				//����
				hitPosition.x -= 55;
				hitPosition.y -= 45;
			}
			else
			{
				//������
				hitPosition.x -= 55;
				hitPosition.y -= 15;
			}
		}
		else
		{
			if (GlobalParameter::upSide)
			{
				//������
				if (GlobalParameter::imageRightSide)
				{
					hitPosition.x += 20;
					hitPosition.y += 25;
				}
				else
				{
					hitPosition.x -= 20;
					hitPosition.y += 25;
				}
			}
			else
			{
				//������
				if (GlobalParameter::imageRightSide)
				{
					hitPosition.x += 20;
					hitPosition.y -= 55;
				}
				else
				{
					hitPosition.x -= 20;
					hitPosition.y -= 55;
				}
			}
		}

		actionSprite->setPosition(hitPosition);

		//����ֱ�Ӽ���
		SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("KnifeHit.plist", "KnifeHit.png");

		int iFrameNum = 5;
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameVec;

		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = frameCache->getSpriteFrameByName(StringUtils::format("KnifeHit%d.png", i));
			frameVec.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(frameVec);
		animation->setLoops(1);
		animation->setDelayPerUnit(0.1f);
		Animate* action = Animate::create(animation);


		//�ص�����
		CallFunc* callFunc = CallFunc::create(
			[&]() {
			actionSpriteRun[index] = false;
			actionSpriteVec[index]->setVisible(false);
		}
		);

		//��϶���
		Action* actions = Sequence::create(action, callFunc, NULL);
		
		//��������ִ�ж���
		actionSprite->setVisible(true);
		actionSprite->runAction(actions);
	}
}