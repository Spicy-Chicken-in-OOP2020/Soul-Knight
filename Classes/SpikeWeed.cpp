#include "SpikeWeed.h"
#include "SafeRoomScene.h"
SpikeWeed::SpikeWeed()
{
	changeTime = 7.0f;
	isStabbing = false;
	this->init();
}

SpikeWeed::~SpikeWeed()
{
	log("A spikeweed is gone.");
}

bool SpikeWeed::init()
{
	if (!Node::init())
		return false;

	//�趨ͼ��
	this->setSprite();

	//ע��ѭ���¼�
	this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);

	return true;
}

void SpikeWeed::setSprite()
{
	//��ȡ�ش�ͼ��
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("SpikeWeed.plist", "SpikeWeed.png");

	int iFrameNum = 4;
	SpriteFrame* frame = NULL;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("SpikeWeed%d.png", i));
		this->frameVec.pushBack(frame);
	}

	this->spikeSprite = Sprite::create();
	this->spikeSprite->setSpriteFrame(*frameVec.begin());
	this->addChild(spikeSprite);

	Size size = spikeSprite->getContentSize();
	this->setContentSize(size);
	this->setAnchorPoint(Point(0, 0));

	frameVec.reverse();
}

void SpikeWeed::spikeUpdate(float dt)
{
	//ֹͣ
	this->unschedule(schedule_selector(SpikeWeed::spikeUpdate));
	/*��ײ�¼�*/
	this->scheduleUpdate();

	//ת�䶯��
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	frameVec.reverse();

	//����ش��Ѿ���չ
	if (this->isStabbing)
	{
		log("BYEBYE");
		//����˳����ת		
		Animate* action = Animate::create(animation);

		//����һ���ص�����
		CallFunc* callFunc = CallFunc::create(
			[&]() {
				this->setIsStabbing(false);
				this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);
		}
		);

		//�����������
		Action* actions = Sequence::create(action, callFunc, NULL);

		//ִ�ж���
		this->spikeSprite->runAction(actions);
	}
	else
	{
		Animate* action = Animate::create(animation);

		//����һ���ص�����
		CallFunc* callFunc = CallFunc::create(
			[&]() {
				this->setIsStabbing(true);
				this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);
		}
		);

		//�����������
		Action* actions = Sequence::create(action, callFunc, NULL);

		//ִ�ж���
		this->spikeSprite->runAction(actions);
	}
}

void SpikeWeed::update(float dt)
{
	//�ж��Ƿ������Ƿ�����ײ
	auto hero = SafeRoomScene::_hero;

	if (hero != nullptr) {
		static int i = 0;
		if (isStabbing&&hero->getBoundingBox().intersectsRect(this->getBoundingBox())) {
			log("stab  me ! %d", i++);
			this->unscheduleUpdate();
			return;
		}
	}
}