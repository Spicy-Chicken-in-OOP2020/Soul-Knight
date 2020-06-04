#include "DialogManager.h"

Layer* DialogManager::createLayer() {
	auto layer = Layer::create();
	return layer;
}

bool DialogManager::init() {
	if (!Layer::create())
		return false;

	this->scheduleUpdate();
	return true;
}

bool DialogManager::bindHero(Hero* hero) {
	_hero = hero;
	return true;
}

bool DialogManager::addDialog(Weapon* weapon) {
	Label* label = Label::create(weapon->weaponName, "Arial", 24);
	label->setVisible(false);
	this->addChild(label);
	objectList.pushBack(weapon);
	dialogList.insert(weapon, label);
	return true;
}

void DialogManager::update(float dt) {
	for (auto dialog :objectList) {
		if (interact(dialog)) {
			Point pos = dialog->getPosition();
			dialogList.at(dialog)->setPosition(pos);
			dialogList.at(dialog)->setVisible(true);
		}
		else dialogList.at(dialog)->setVisible(false);
	}
}

bool DialogManager::interact(Node* object) {
	Rect heroRect = _hero->getBoundingBox();
	Point pos_object = object->getPosition();
	if (heroRect.containsPoint(pos_object))
		return true;
	else return false;
}