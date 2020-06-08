#include "ShopSystem.h"
#include "Items.h"
#include "GlobalParameter.h"
#include "Hero.h"
#include "SafeRoomScene.h"

bool ShopSystem::init() {
	if (!Layer::init())
		return false;
	/*pause*/
	this->scheduleUpdate();
	this->setVisible(true);

	this->isTouch1 = false;
	this->isTouch2 = false;
	this->isTouch3 = false;
	this->isTouch4 = false;
	this->isTouch5 = false;

	/*UI*/
	_ui = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ShopSystem.ExportJson");
	/*button~*/
	auto button1 = dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_1"));
	button1->addTouchEventListener(this, toucheventselector(ShopSystem::button1Callfunc));
	auto button2 = dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_2"));
	button2->addTouchEventListener(this, toucheventselector(ShopSystem::button2Callfunc));
	auto button3 = dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_3"));
	button3->addTouchEventListener(this, toucheventselector(ShopSystem::button3Callfunc));
	auto button4 = dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_4"));
	button4->addTouchEventListener(this, toucheventselector(ShopSystem::button4Callfunc));
	auto button5 = dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_5"));
	button5->addTouchEventListener(this, toucheventselector(ShopSystem::button5Callfunc));
	auto buttonBack= dynamic_cast<Button*>(Helper::seekWidgetByName(_ui, "Button_back"));
	buttonBack->addTouchEventListener(this, toucheventselector(ShopSystem::buttonBackCallfunc));

	this->addChild(_ui);
	
	return true;
}

void ShopSystem::button1Callfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (this->isTouch1)
			return;
		isTouch1 = true;
		/*Price*/
		auto price1 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(_ui, "Price_1"));
		String text= price1->getStringValue();
		auto price = text.intValue();

		if (GlobalParameter::_diamond < price) {
			log("no enough money");
			return;
		}
		log("purchass successfully ,thank you !");
		/*cost*/
		GlobalParameter::_diamond -= price;
		/*items*/
		auto items = Items::createItems(KNIFE_TAG, GlobalParameter::hero->getPosition());
		auto layer = dynamic_cast<Layer*>(GlobalParameter::mapNow->getParent());
		if (layer) {
			layer->addChild(items, 2);
		}
		
		break;
	}
}

void ShopSystem::button2Callfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (this->isTouch2)
			return;
		isTouch2 = true;
		/*Price*/
		auto price2 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(_ui, "Price_2"));
		String text = price2->getStringValue();
		auto price = text.intValue();

		if (GlobalParameter::_diamond < price) {
			log("no enough money");
			return;
		}
		log("purchass successfully ,thank you !");
		/*cost*/
		GlobalParameter::_diamond -= price;
		/*items*/
		auto items = Items::createItems(GUN_TAG, GlobalParameter::hero->getPosition());
		auto layer = dynamic_cast<Layer*>(GlobalParameter::mapNow->getParent());
		if (layer) {
			layer->addChild(items, 2);
		}

		break;
	}
}

void ShopSystem::button3Callfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (this->isTouch3)
			return;
		isTouch3 = true;
		/*Price*/
		auto price3 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(_ui, "Price_3"));
		String text = price3->getStringValue();
		auto price = text.intValue();

		if (GlobalParameter::_diamond < price) {
			log("no enough money");
			return;
		}
		log("purchass successfully ,thank you !");
		/*cost*/
		GlobalParameter::_diamond -= price;
		/*items*/
		auto items = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
		auto layer = dynamic_cast<Layer*>(GlobalParameter::mapNow->getParent());
		if (layer) {
			layer->addChild(items, 2);
		}

		break;
	}
}

void ShopSystem::button4Callfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (this->isTouch4)
			return;
		isTouch4 = true;
		/*Price*/
		auto price4 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(_ui, "Price_4"));
		String text = price4->getStringValue();
		auto price = text.intValue();

		if (GlobalParameter::_diamond < price) {
			log("no enough money");
			return;
		}
		log("purchass successfully ,thank you !");
		/*cost*/
		GlobalParameter::_diamond -= price;
		/*items*/
		int itemsId = rand() % 4 + 4;

		auto items = Items::createItems(itemsId, GlobalParameter::hero->getPosition());
		auto layer = dynamic_cast<Layer*>(GlobalParameter::mapNow->getParent());
		if (layer) {
			layer->addChild(items, 2);
		}

		break;
	}
}

void ShopSystem::button5Callfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (this->isTouch5)
			return;
		isTouch5 = true;
		/*Price*/
		auto price5 = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(_ui, "Price_5"));
		String text = price5->getStringValue();
		auto price = text.intValue();

		if (GlobalParameter::_diamond < price) {
			log("no enough money");
			return;
		}
		log("purchass successfully ,thank you !");
		/*cost*/
		GlobalParameter::_diamond -= price;
		/*items*/
		int itemsId = rand() % 4 + 4;

		auto items = Items::createItems(itemsId, GlobalParameter::hero->getPosition());
		auto layer = dynamic_cast<Layer*>(GlobalParameter::mapNow->getParent());
		if (layer) {
			layer->addChild(items, 2);
		}

		break;
	}
}

void ShopSystem::buttonBackCallfunc(Ref*, TouchEventType type) {
	switch (type) {
	case TouchEventType::TOUCH_EVENT_ENDED:
		this->removeFromParentAndCleanup(true);
		break;
	}
}