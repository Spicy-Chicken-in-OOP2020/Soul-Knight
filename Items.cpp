#include "Items.h"
#include "SafeRoomScene.h"
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

Items* Items::createItems(int itemsTag) {
	Items* items = Items::create();
	/*��������*/
	std::string spritePath = StringUtils::format("Items_%d.png", itemsTag);
	items->_sprite = Sprite::create(spritePath);
	items->addChild(items->_sprite);

	/*��������*/
	items->setTag(itemsTag);
	
	items->setContentSize(items->_sprite->getContentSize());
	items->setAnchorPoint(Point(0, 0));
	
	/*���õ���λ��,��ͼ���ȡ*/
	items->setPosition(Point(SafeRoomScene::_hero->getPosition().x-50, SafeRoomScene::_hero->getPosition().y - 50));

	/*�����ｻ��*/
	items->keyBoard_k_register();

	/*ע�����¼�*/
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
	}
}

void Items::update(float dt) {
	int tag = this->getTag();
	
	if (this->getBoundingBox().intersectsRect(SafeRoomScene::_hero->getBoundingBox())) {
		switch (tag) {
		case BS_TAG: {
			/*��ʯ���Ӳ���to do*/
			MoveTo* moveToBS = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToBS);
			this->removeFromParentAndCleanup(true);
			log("bs add\n");
			break; }
		case JB_TAG: {
			/*������Ӳ���to do*/
			MoveTo* moveToJB = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToJB);
			this->removeFromParentAndCleanup(true);
			log("jb add\n");
			break; }
		}
	}
}
