#include "PauseLayer1.h"
#include "StartScene.h"



PauseLayer* PauseLayer::_pauseLayer = nullptr;

PauseLayer* PauseLayer::createPauseLayer() {
	if (_pauseLayer != nullptr)
		return _pauseLayer;

	_pauseLayer = PauseLayer::create();

	return _pauseLayer;
}

bool PauseLayer::init() {
	if (!Layer::init())
		return false;

	

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("pauseLayer_1.ExportJson");
	Button* Btn_home = (Button*)Helper::seekWidgetByName(UI, "Btn_home");
	Button* Btn_resume = (Button*)Helper::seekWidgetByName(UI, "Btn_resume");

	Btn_home->addTouchEventListener(this, toucheventselector(PauseLayer::homeEvent));
	Btn_resume->addTouchEventListener(this, toucheventselector(PauseLayer::resumeEvent));


	auto Btn_setting = CheckBox::create("Btn_setting.png",
		"Btn_setting_PressDown.png");
	Btn_setting->setPosition(Point(visibleSize.width/2+165, visibleSize.height/2-85));
	this->addChild(Btn_setting, 3);
	Btn_setting->addEventListener(CC_CALLBACK_2(PauseLayer::settingSelectedEvent, this));

	Btn_BGmusic= CheckBox::create("Btn_backgroundmusic.png",
		"Btn_backgroundmusic_PressDown.png");
	Btn_BGmusic->setPosition(Point(visibleSize.width / 2+45, visibleSize.height / 14-85));
	this->addChild(Btn_BGmusic, 3);
	Btn_BGmusic->setVisible(false);
	Btn_BGmusic->addEventListener(CC_CALLBACK_2(PauseLayer::BGmusicSelectedEvent, this));


	Btn_effectMusic = CheckBox::create("Btn_effect.png",
		"Btn_effect_PressDown.png");
	Btn_effectMusic->setPosition(Point(visibleSize.width / 2-36, visibleSize.height / 14-85));
	this->addChild(Btn_effectMusic, 3);
	Btn_effectMusic->setVisible(false);
	Btn_effectMusic->addEventListener(CC_CALLBACK_2(PauseLayer::effectMusicSelectedEvent, this));

	
	
	this->addChild(UI);
	return true;
}

void PauseLayer::settingSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	switch (type){
	case cocos2d::ui::CheckBox::EventType::SELECTED:{
		MoveBy* flowUp = MoveBy::create(0.3f, Point(0, 73));
		Btn_effectMusic->setVisible(true);
		Btn_effectMusic->runAction(flowUp);
	}break;

	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		MoveBy* flowDown = MoveBy::create(0.3f, Point(0, -73));
		Btn_effectMusic->runAction(flowDown);
	}break;
	}

	switch (type) {
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		MoveBy* flowUp = MoveBy::create(0.3f, Point(0, 73));
		Btn_BGmusic->setVisible(true);
		Btn_BGmusic->runAction(flowUp);
	}break;

	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		MoveBy* flowDown = MoveBy::create(0.3f, Point(0, -73));
		Btn_BGmusic->runAction(flowDown);
	}break;
	}
}

void PauseLayer::BGmusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isBGmusicplaying = false;
	}break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		isBGmusicplaying = true;
	}break;
	}
}

void PauseLayer::effectMusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type) {
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED: {
		isEffecMusicTurnOn = false;
	}break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED: {
		isEffecMusicTurnOn = true;
	}break;
	}
}

void PauseLayer::homeEvent(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED: {
		Director::getInstance()->replaceScene(StartScene::createScene());
	}break;
	}
}

void PauseLayer::resumeEvent(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED: {
		_pauseLayer->setVisible(false);
		log("Game Continued");
		//��Ϸ����
		CCDirector::sharedDirector()->resume();
	}break;
	}
}

bool PauseLayer::BGmusic() {
	return isBGmusicplaying;
}

bool PauseLayer::effectMusic() {
	return isEffecMusicTurnOn;
}

void PauseLayer::setHeroHead(Sprite* heroHead) {
	m_heroHead = heroHead;
}

void PauseLayer::setBuff(Sprite* buff, int i) {

}