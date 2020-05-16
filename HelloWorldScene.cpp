/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"


Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//加载主界面UI
	auto mainUI = cocostudio::GUIReader::getInstance()->
		widgetFromJsonFile("MainUI.ExportJson");

	log("Loading mainUI successfully\n");

	//加入
	this->addChild(mainUI);

	//获取按钮事件
	Button* stopButton = (Button*)Helper::seekWidgetByName(mainUI, "stopButton");

	//添加按钮单击监听
	//stopButton->addTouchEventListener(this, toucheventselector(HelloWorld::stopButtonClick));

	//获取主角HP
	//进度条
	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	//当前生命
	auto playerHpNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpNow");
	//最大生命
	auto playerHpMax = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpMax");

	//获取主角护甲
	//进度条
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	//当前生命
	auto playerDefendenseNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseNow");
	//最大生命
	auto playerDefendenseMax = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseMax");

	//获取主角MP
	//进度条
	auto playerMpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerMpUI");
	//当前生命
	auto playerMpNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpNow");
	//最大生命
	auto playerMpMax = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpMax");


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::stopButtonClick(Ref*, TouchEventType type)
{
	//根据类型判断
	switch (type)
	{
		//松开后，打开暂停界面
	case TouchEventType::TOUCH_EVENT_ENDED:
		log("Stop Button is Clicked!");
		break;
	}
}
