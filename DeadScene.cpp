#include "DeadScene.h"

Scene* DeadScene::createScene(){
	auto layer = DeadScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

bool DeadScene::init() {
	if (!Layer::init())
		return false;

	click = false;

	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("deadScene_1.ExportJson");
	this->addChild(UI);

	Button* Btn_continue = (Button*)Helper::seekWidgetByName(UI, "Btn_continue");
	Btn_continue->addTouchEventListener(this, toucheventselector(DeadScene::continueEvent));

	label_time_m = (Text*)Helper::seekWidgetByName(UI, "label_time_m");
	label_time_s = (Text*)Helper::seekWidgetByName(UI, "label_time_s");
	label_coin = (Text*)Helper::seekWidgetByName(UI, "label_coin");
	Color4B coin = ccc4(255,215,0,255);
	label_coin->setTextColor(coin);
	Color4B currency = ccc4(0, 191, 255, 255);
	label_currency = (Text*)Helper::seekWidgetByName(UI, "label_currency");
	label_currency->setTextColor(currency);
	label_totalCurrency = (Text*)Helper::seekWidgetByName(UI, "label_totalCurrency");
	label_kill = (Text*)Helper::seekWidgetByName(UI, "label_kill");

	setLabel();
	
	setValue(4, 2741, 64, 273, 569, 1234);
	return true;
}

void DeadScene::continueEvent(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED: {
		if (click == false) {
			setLabel();
			click = true;
		}
		else {
			//TODO:返回安全房间





		}
	}break;
	}

}

bool DeadScene::bindHero(Hero* _hero) {
	hero = _hero->getSprite();
	hero->setPosition(Point(120, 500));
	this->addChild(hero, 2);
	return true;
}

void DeadScene::setValue(int _rateOfProgress, int _time, int _coin, int _currency, int _totalCurrency, int _kill) {
	rateOfProgress = _rateOfProgress;
	time = _time;
	coin = _coin;
	currency = _currency;
	totalCurrency = _totalCurrency;
	kill = _kill;
}

void DeadScene::setLabel() {
	int m = time / 60;
	int s = time % 60;
	label_time_m->setString(Value(m).asString());
	if (s == 0) 
		label_time_s->setString("00");
	else label_time_s -> setString(Value(s).asString());
	label_coin ->setString(Value(coin).asString());
	label_currency -> setString(Value(currency).asString());
	label_totalCurrency -> setString(Value(totalCurrency).asString());
	label_kill -> setString(Value(kill).asString());
	
	switch (rateOfProgress) {
	case 0: {
		MoveTo* moveto = MoveTo::create(0.5f, Point(120, 500));
		hero->runAction(moveto);
	} break;
	case 1: {
		MoveTo* moveto = MoveTo::create(0.5f, Point(270, 500));
		hero->runAction(moveto);
	} break;
	case 2: {
		MoveTo* moveto = MoveTo::create(0.8f, Point(430, 500));
		hero->runAction(moveto);
	} break;
	case 3: {
		MoveTo* moveto = MoveTo::create(0.9f, Point(590, 500));
		hero->runAction(moveto);
	} break;
	case 4: {
		MoveTo* moveto = MoveTo::create(1.1f, Point(740, 500));
		hero->runAction(moveto);
	} break;
	case 5: {
		MoveTo* moveto = MoveTo::create(1.5f, Point(895, 500));
		hero->runAction(moveto);
	} break;
	}
}