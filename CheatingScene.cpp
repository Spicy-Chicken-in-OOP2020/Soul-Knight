#include"CheatingScene.h"

Scene* CheatingScene::createScene() {
	auto scene = Scene::create();
	auto layer =CheatingScene::create();
	scene->addChild(layer);
	return scene;
}

bool CheatingScene::init() {
	if (!Scene::create())
		return true;
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CheatingScene_1.ExportJson");
	this->addChild(UI);

	CheckBox* checkBox_hp = (CheckBox*)Helper::seekWidgetByName(UI, "CheckBox_hp");
	checkBox_hp->addEventListener(CC_CALLBACK_2(CheatingScene::hpEvent, this));

	CheckBox* checkBox_mp = (CheckBox*)Helper::seekWidgetByName(UI, "CheckBox_mp");
	checkBox_mp->addEventListener(CC_CALLBACK_2(CheatingScene::mpEvent, this));

	CheckBox* checkBox_coin = (CheckBox*)Helper::seekWidgetByName(UI, "CheckBox_coin");
	checkBox_coin->addEventListener(CC_CALLBACK_2(CheatingScene::coinEvent, this));

	Button* Btn_back = (Button*)Helper::seekWidgetByName(UI, "Button_back");
	Btn_back->addClickEventListener(CC_CALLBACK_1(CheatingScene::backEvent, this));

	isInfiniteHp = false;
	isInfiniteMp = false;
	isInfiniteCoin = false;

	return true;
}

bool CheatingScene::getInfiniteHp() {
	return isInfiniteHp;
}

bool CheatingScene::getInfiniteMp() {
	return isInfiniteMp;
}

bool CheatingScene::getInfiniteCoin() {
	return isInfiniteCoin;
}

void CheatingScene::hpEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	switch(type) {
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isInfiniteHp = true;
	}break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		isInfiniteHp = false;
	}break;
	}
}

void CheatingScene::mpEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	switch (type) {
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isInfiniteMp = true;
	}break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		isInfiniteMp = false;
	}break;
	}
}

void CheatingScene::coinEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	switch (type) {
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isInfiniteCoin = true;
	}break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		isInfiniteCoin = false;
	}break;
	}
}

void CheatingScene::backEvent(Ref*) {
	//∑µªÿ‘›Õ£ΩÁ√Ê
}