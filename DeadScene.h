#ifndef __DeadScene_H__
#define __DeadScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Hero.h"


using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;

class DeadScene :public Layer {
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(DeadScene);
    bool bindHero(Hero* hero);  //绑定英雄

    //设置数据：游戏进度（1至5）、时间（秒）、金币、游戏内货币、总货币、杀敌数
    void setValue(int rateOfProgress, int time, int coin, int currency, int totalCurrency, int kill);
    void continueEvent(Ref*, TouchEventType type);
private:
    Sprite* hero;
    int rateOfProgress;
    int time;
    Text* label_time_m;
    Text* label_time_s;
    int coin;
    Text* label_coin;
    int currency;
    Text* label_currency;
    int totalCurrency;
    Text* label_totalCurrency;
    int kill;
    Text* label_kill;
    void setLabel();
    bool click;
};
#endif // !__DeadScene_H__
#pragma once
