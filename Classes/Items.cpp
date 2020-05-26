#include "Items.h"
#include "SafeRoomScene.h"
#include "Knife.h"
#include "gun.h"
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

	items->setContentSize(items->_sprite->getContentSize());
	items->setAnchorPoint(Point(0, 0));

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
				this->removeFromParentAndCleanup(true);
		}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

}

void Items::effectOfItems(int itemsTag) {
	switch (itemsTag) {
	case HP_ADD_TAG:
		//SafeRoomScene::_hero->setHp(SafeRoomScene::_hero->gethp() + HP_ADD_NUM);
		log("hp add\n");
		break;
	case MP_ADD_TAG:
		//SafeRoomScene::_hero->setMp(SafeRoomScene::_hero->getmp() + MP_ADD_NUM);
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
		ShootController* shootContro = ShootController::create();
		Gun* gun = new Gun(shootContro, 3, "枪支");
		GlobalParameter::hero->setWeapon(gun);
		break;
	}
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
}