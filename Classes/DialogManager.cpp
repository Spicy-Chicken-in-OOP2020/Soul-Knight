#include "DialogManager.h"

Scene* DialogManager::createDialog(const Vec2& pos,std::string str,bool needDisappear) {
	auto scene = Scene::create();
	auto layer = DialogManager::create();
	Label* label = Label::create(str, "Arial", 24);
	label->setPosition(pos);
	layer->addChild(label);
	scene->addChild(layer);
	
	if (needDisappear)
	{
		layer->registeKeyBoardEvent();
	}

	return scene;
}

bool DialogManager::init() {
	if (!Layer::create())
		return false;
}

void DialogManager::registeKeyBoardEvent() {
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_K:
			this->setVisible(false);
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
}

