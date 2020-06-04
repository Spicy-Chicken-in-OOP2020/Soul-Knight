#include "HeroChooseLayer.h"

Layer* HeroChooseLayer::createLayer() {
	auto layer = Layer::create();
	return layer;
}

bool HeroChooseLayer::init() {
	if (!Layer::create())
		return false;

	auto UI= cocostudio::GUIReader::getInstance()->widgetFromJsonFile("heroChooseLayer_1.ExportJson");
	this->addChild(UI);
	hp = (Text*)Helper::seekWidgetByName(UI, "Label_hp");
	mp = (Text*)Helper::seekWidgetByName(UI, "Label_mp");
	defense = (Text*)Helper::seekWidgetByName(UI, "Label_defense");
	totalCurrency = (Text*)Helper::seekWidgetByName(UI, "Label_totalCurrency");
	level = (Text*)Helper::seekWidgetByName(UI, "Label_heroLevel");
	name = (Text*)Helper::seekWidgetByName(UI, "Label_heroName");

	hpLoadingBar = (LoadingBar*)Helper::seekWidgetByName(UI, "hpBar");
	mpLoadingBar = (LoadingBar*)Helper::seekWidgetByName(UI, "mpBar");
	defenseLoadingBar = (LoadingBar*)Helper::seekWidgetByName(UI, "defenseBar");
	
	Btn_left = (Button*)Helper::seekWidgetByName(UI, "Btn_left");
	Btn_left->addClickEventListener(CC_CALLBACK_1(HeroChooseLayer::leftEvent, this));
	Btn_left->setVisible(false);
	Btn_right = (Button*)Helper::seekWidgetByName(UI, "Btn_right");
	Btn_right->addClickEventListener(CC_CALLBACK_1(HeroChooseLayer::rightEvent, this));
	Button* Btn_back = (Button*)Helper::seekWidgetByName(UI, "Btn_back");
	Btn_back->addClickEventListener(CC_CALLBACK_1(HeroChooseLayer::backEvent, this));
	Button* Btn_play = (Button*)Helper::seekWidgetByName(UI, "Btn_play");
	Btn_play->addClickEventListener(CC_CALLBACK_1(HeroChooseLayer::playEvent, this));
	Button* Btn_levelUp = (Button*)Helper::seekWidgetByName(UI, "Btn_levelUp");
	Btn_levelUp ->addClickEventListener(CC_CALLBACK_1(HeroChooseLayer::levelUpEvent, this));

	heroNum = 0;
	now = 1;
	return true;
}

void HeroChooseLayer::addHero(Hero* hero){
	heroNum++;
	heroList.insert(heroNum,hero);
	hero->setPosition(512, 330);
	hero->setVisible(false);
	this->addChild(hero);
	if (heroNum == 1) 
		setLabel();
}

void HeroChooseLayer::leftEvent(Ref*) {
	now--;
	if (now == 1)
		Btn_left->setVisible(false);
	if(now<heroNum)
		Btn_right->setVisible(true);
	heroList.at(now + 1)->setVisible(false);
	setLabel();
}

void HeroChooseLayer::rightEvent(Ref*) {
	now++;
	if (now == heroNum)
		Btn_right->setVisible(false);
	if (now > 1);
		Btn_left->setVisible(true);
	heroList.at(now -1)->setVisible(true);
	setLabel();
}

void HeroChooseLayer::backEvent(Ref*) {
	//返回开始场景
}

void HeroChooseLayer::playEvent(Ref*) {
	//确认选择的hero 调用getChosenHero函数 界面消失
}

void HeroChooseLayer::levelUpEvent(Ref*) {
	//heroList.at(now)->levelUp()
	//减1000
}

void HeroChooseLayer::setLabel() {
	hp->setString(Value(heroList.at(now)->gethpMax()).asString());
	hpLoadingBar->setPercent(Value(heroList.at(now)->gethpMax()).asInt());
	mp->setString(Value(heroList.at(now)->getmpMax()).asString());
	mpLoadingBar->setPercent(Value(heroList.at(now)->getmpMax()).asInt());
	defense->setString(Value(heroList.at(now)->getdefenseMax()).asString());
	defenseLoadingBar->setPercent(Value(heroList.at(now)->getdefenseMax()).asInt());

	name->setString(heroList.at(now)->name);
	totalCurrency->setString(Value(_totalCurrency).asString());

	heroList.at(now)->setVisible(true);
}

void HeroChooseLayer::setTotalCurrency(int t) {
	_totalCurrency = t;
}