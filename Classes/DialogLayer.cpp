#include "DialogLayer.h"

Layer* DialogLayer::createLayer() {
	auto layer = Layer::create();
	return layer;
}

bool DialogLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//this->scheduleUpdate();
	return true;
}

bool DialogLayer::bindHero(Hero* hero) {
	m_hero = hero;
	return true;
}

bool DialogLayer::bindObject(Node* object) {
	m_object = object;
	//label = Label::create(m_object->text,"Arial",24);
	this->addChild(label);
	return true;
}

void DialogLayer::update(float delta) {
	Rect heroRect = m_hero->getBoundingBox();
	Point pos_object = m_object->getPosition();
	label->setPosition(pos_object);
	if (heroRect.containsPoint(pos_object)) 
		needToShow = true;
	
	else needToShow=false;
}

bool DialogLayer::getShowState(){
	return needToShow;
}