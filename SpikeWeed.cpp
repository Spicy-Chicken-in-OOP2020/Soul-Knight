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

	//设定图像
	this->setSprite();

	//注册循环事件
	this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);

	return true;
}

void SpikeWeed::setSprite()
{
	//读取地刺图像
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
	//停止
	this->unschedule(schedule_selector(SpikeWeed::spikeUpdate));
	/*碰撞事件*/
	this->scheduleUpdate();

	//转变动画
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	frameVec.reverse();

	//如果地刺已经伸展
	if (this->isStabbing)
	{
		log("BYEBYE");
		//动画顺序逆转		
		Animate* action = Animate::create(animation);

		//创建一个回调函数
		CallFunc* callFunc = CallFunc::create(
			[&]() {
				this->setIsStabbing(false);
				this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);
		}
		);

		//创建动作组合
		Action* actions = Sequence::create(action, callFunc, NULL);

		//执行动作
		this->spikeSprite->runAction(actions);
	}
	else
	{
		Animate* action = Animate::create(animation);

		//创建一个回调函数
		CallFunc* callFunc = CallFunc::create(
			[&]() {
				this->setIsStabbing(true);
				this->schedule(schedule_selector(SpikeWeed::spikeUpdate), this->changeTime);
		}
		);

		//创建动作组合
		Action* actions = Sequence::create(action, callFunc, NULL);

		//执行动作
		this->spikeSprite->runAction(actions);
	}
}

void SpikeWeed::update(float dt)
{
	//判断是否与主角发生碰撞
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