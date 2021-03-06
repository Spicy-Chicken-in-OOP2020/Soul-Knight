#include "Items.h"
#include "SafeRoomScene.h"
#include "Knife.h"
#include "gun.h"
#include "QuickGun.h"
#include "DialogManager.h"
Items::Items() :_sprite(nullptr) {

};

Items::~Items() {

}

bool Items::init() {
	if (!Node::init()) {
		return false;
	}

	return true;
}

Items* Items::createItems(int itemsTag, Point position) {
	Items* items = Items::create();
	/*创建精灵*/
	std::string spritePath = StringUtils::format("Items_%d.png", itemsTag);
	items->_sprite = Sprite::create(spritePath);
	items->addChild(items->_sprite);

	/*道具属性*/
	items->setTag(itemsTag);

	/*在此添加文本*/
	switch (itemsTag)
	{
	case KNIFE_TAG:
	{
		break;
	}
	case GUN_TAG:
	{
		Label* label = Label::create("小伙子，\n你真的很有经验", "Arial", 24);
		
		items->addChild(label);
		break;
	}
	case QUICKGUN_TAG:
	{
		Label* label = Label::create("小伙子，\n你真的很有经验", "Arial", 24);
		items->addChild(label);
		break;
	}
	}

	/*宝箱类增大范围判定*/
	if (items->getTag() == BAOXIANG_TAG)
	{
		Size size = items->_sprite->getContentSize();
		size.width += 20;
		size.height += 20;
		items->setContentSize(size);
		items->setAnchorPoint(Point(0, 0));
	}
	else
	{
		items->setContentSize(items->_sprite->getContentSize());
		items->setAnchorPoint(Point(0, 0));
	}

	/*设置道具位置,从图层读取*/
	items->setPosition(position);

	/*与人物交互*/
	items->keyBoard_k_register();

	/*注册监控事件*/
	if (itemsTag == BS_TAG || itemsTag == JB_TAG)
		items->scheduleUpdate();

	return items;
}

void Items::keyBoard_k_register() {
	auto keyBoardListener = EventListenerKeyboard::create();

	keyBoardListener->onKeyPressed= [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_K:  //k
			if (this->getBoundingBox().intersectsRect(SafeRoomScene::_hero->getBoundingBox())) {
				effectOfItems(this->getTag());
				{
					//如果这个物品属于宝箱，则不需要回收，仅需更改图片即可
					if (this->getTag()==BAOXIANG_TAG)
					{
						Sprite* newSprite = Sprite::create("Items_9.png");
						this->_sprite->removeFromParentAndCleanup(true);
						this->_sprite = newSprite;
						this->addChild(this->_sprite);
						//标记已完成替换
						this->setTag(OPENED_BAOXIANG_TAG+0);
					}
					else if (this->getTag()!=OPENED_BAOXIANG_TAG+0)
					{
						this->removeFromParentAndCleanup(true);
					}
				}
		}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

}

void Items::effectOfItems(int itemsTag) {
	switch (itemsTag) {
	case HP_ADD_TAG:
		GlobalParameter::hero->setHp(GlobalParameter::hero->gethp() + HP_ADD_NUM);
		log("hp add\n");
		break;
	case MP_ADD_TAG:
		GlobalParameter::hero->setMp(GlobalParameter::hero->getmp() + MP_ADD_NUM);
		log("mp add\n");
		break;
	case KNIFE_TAG:
	{
		//丢弃武器
		this->throwWeapon();
		//将武器设置为刀
		HitController* hitContro = HitController::create();
		Knife* knife = new Knife(hitContro, 3, "匕首");
		GlobalParameter::hero->setWeapon(knife);
		break;
	}
	case GUN_TAG:
	{
		//丢弃武器
		this->throwWeapon();
		//将武器设置为枪支
		Gun* gun = new Gun(3, "枪支");
		GlobalParameter::hero->setWeapon(gun);
		break;
	}
	case QUICKGUN_TAG:
	{
		//丢弃武器
		this->throwWeapon();
		//将武器设置为冲锋枪
		QuickGun *quickGun = new QuickGun(2, "冲锋枪");
		GlobalParameter::hero->setWeapon(quickGun);
		
		break;
	}
	case BAOXIANG_TAG:
		//宝箱
	{
		//打开宝箱
		//随机一把武器
		double randomItem = CCRANDOM_0_1();
		//确认种类
		if (randomItem < 0.2f)
		{
			Items* item = Items::createItems(HP_ADD_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.4f)
		{
			Items* item = Items::createItems(MP_ADD_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.6f)
		{
			Items* item = Items::createItems(GUN_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.7f)
		{
			Items* item = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.9f)
		{
			Items* item = Items::createItems(KNIFE_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else
		{
			//待添加

		}

		break;
	}
	//OPENED_BAOXIANG_TAG不需要发生交互
	}
}

void Items::update(float dt) {
	int tag = this->getTag();
	
	if (this->getBoundingBox().intersectsRect(SafeRoomScene::_hero->getBoundingBox())) {
		switch (tag) {
		case BS_TAG: {
			/*宝石增加操作to do*/
			MoveTo* moveToBS = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToBS);
			this->removeFromParentAndCleanup(true);
			log("bs add\n");
			break; }
		case JB_TAG: {
			/*金币增加操作to do*/
			MoveTo* moveToJB = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToJB);
			this->removeFromParentAndCleanup(true);
			log("jb add\n");
			break; }
		}
	}
}

void Items::throwWeapon()
{
	//丢弃之前的武器
	Weapon* weapon = GlobalParameter::hero->removeWeapon();
	if (weapon == nullptr)
		return;
	//根据武器类型
	CCString weaponType = typeid(*weapon).name();
	//确认武器类型
	if (weaponType._string == "class Gun")
	{
		Items* item = Items::createItems(GUN_TAG,GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
	else if (weaponType._string == "class Knife")
	{
		Items* item = Items::createItems(KNIFE_TAG, GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
	else if (weaponType._string == "class QuickGun")
	{
		Items* item = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
}