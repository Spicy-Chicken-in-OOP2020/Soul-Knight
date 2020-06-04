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
    bool bindHero(Hero* hero);  //��Ӣ��

    //�������ݣ���Ϸ���ȣ�1��5����ʱ�䣨�룩����ҡ���Ϸ�ڻ��ҡ��ܻ��ҡ�ɱ����
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
