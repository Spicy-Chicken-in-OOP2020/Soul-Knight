#include "ShopSystem.h"


Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}


	//加载
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ShopSystem_1.ExportJson");
	this->addChild(UI);

	//读取退出按钮
	Button *exitButton = (Button*)Helper::seekWidgetByName(UI, "ButtonExit");

	//读取控件(即购买按钮)
	buttons[0] = (Button*)Helper::seekWidgetByName(UI, "Button1");
	buttons[1] = (Button*)Helper::seekWidgetByName(UI, "Button2");
	buttons[2] = (Button*)Helper::seekWidgetByName(UI, "Button3");
	buttons[3] = (Button*)Helper::seekWidgetByName(UI, "Button4");
	buttons[4] = (Button*)Helper::seekWidgetByName(UI, "Button5");

	//读取文本(即商品名)
	texts[0] = (Text*)Helper::seekWidgetByName(UI, "Label1");
	texts[1] = (Text*)Helper::seekWidgetByName(UI, "Label2");
	texts[2] = (Text*)Helper::seekWidgetByName(UI, "Label3");
	texts[3] = (Text*)Helper::seekWidgetByName(UI, "Label4");
	texts[4] = (Text*)Helper::seekWidgetByName(UI, "Label5");

	//读取图片(即商品图片)
	images[0] = (Image*)Helper::seekWidgetByName(UI, "Image1");
	images[1] = (Image*)Helper::seekWidgetByName(UI, "Image2");
	images[2] = (Image*)Helper::seekWidgetByName(UI, "Image3");
	images[3] = (Image*)Helper::seekWidgetByName(UI, "Image4");
	images[4] = (Image*)Helper::seekWidgetByName(UI, "Image5");

	//读取文本(即商品价格)
    price[0] = (Text*)Helper::seekWidgetByName(UI, "Price1");
	price[1] = (Text*)Helper::seekWidgetByName(UI, "Price2");
	price[2] = (Text*)Helper::seekWidgetByName(UI, "Price3");
	price[3] = (Text*)Helper::seekWidgetByName(UI, "Price4");
	price[4] = (Text*)Helper::seekWidgetByName(UI, "Price5");

	//测试更改
	this->setWareInformation(0, "Normal Gun", 10, "sss");

	return true;
}

void TollgateScene::setWareInformation(int i, String name, int prices, String ImageFileRoad)
{
	price[i]->setText(StringUtils::format("$%d", prices));
	texts[i]->setText(name.getCString());
}