#ifndef __HeroChooseLayer_H__
#define __HeroChooseLayer_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "Hero.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;

class HeroChooseLayer :public Layer {
public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(HeroChooseLayer);
	void leftEvent(Ref*);
	void rightEvent(Ref*);
	void backEvent(Ref*);
	void playEvent(Ref*);
	void levelUpEvent(Ref*);
	
	void setTotalCurrency(int);
	/*加入供选择的英雄*/
	void addHero(Hero* hero);

	/*返回选中的英雄*/
	Hero* getChosenHero();
private:
	int heroNum;
	int now;
	Hero* nowHero;
	Map<int,Hero*> heroList;
	Text* hp;
	Text* mp;
	Text* defense;
	Text* name;
	int _totalCurrency;
	Text* totalCurrency;
	Text* level;
	LoadingBar* hpLoadingBar;
	LoadingBar* mpLoadingBar;
	LoadingBar* defenseLoadingBar;
	Button* Btn_left;
	Button* Btn_right;
	void setLabel();
};

#endif