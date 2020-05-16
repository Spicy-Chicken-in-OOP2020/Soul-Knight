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

	//����������UI
	auto mainUI = cocostudio::GUIReader::getInstance()->
		widgetFromJsonFile("MainUI.ExportJson");

	log("Loading mainUI successfully\n");

	//����
	this->addChild(mainUI);

	//��ȡ��ť�¼�
	Button* stopButton = (Button*)Helper::seekWidgetByName(mainUI, "stopButton");

	//��Ӱ�ť��������
	//stopButton->addTouchEventListener(this, toucheventselector(HelloWorld::stopButtonClick));

	//��ȡ����HP
	//������
	auto playerHpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerHpUI");
	//��ǰ����
	auto playerHpNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpNow");
	//�������
	auto playerHpMax = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryHpMax");

	//��ȡ���ǻ���
	//������
	auto playerDefendenseUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerDefendenseUI");
	//��ǰ����
	auto playerDefendenseNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseNow");
	//�������
	auto playerDefendenseMax = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryDefendenseMax");

	//��ȡ����MP
	//������
	auto playerMpUI = (LoadingBar*)Helper::seekWidgetByName(mainUI, "PlayerMpUI");
	//��ǰ����
	auto playerMpNow = (Label*)Helper::seekWidgetByName(mainUI, "BoundaryMpNow");
	//�������
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
	//���������ж�
	switch (type)
	{
		//�ɿ��󣬴���ͣ����
	case TouchEventType::TOUCH_EVENT_ENDED:
		log("Stop Button is Clicked!");
		break;
	}
}
