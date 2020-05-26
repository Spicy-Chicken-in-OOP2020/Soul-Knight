#include "DialogManager.h"

bool DialogManager::init() {
	this->scheduleUpdate();
	return true;
}

void DialogManager::addDialog(Hero* hero, Node* object) {
	DialogLayer* dialogLayer = DialogLayer::create();
	dialogLayer->bindHero(hero);
	dialogLayer->bindObject(object);
	this->addChild(dialogLayer);
	dialogList.pushBack(dialogLayer);
}

void DialogManager::update(float dt) {
	for (auto dialogLayer : dialogList) {
		if (dialogLayer->getShowState())
			dialogLayer->setVisible(true);
		else dialogLayer->setVisible(false);
	}
}