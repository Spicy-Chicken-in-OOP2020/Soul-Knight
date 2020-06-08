#ifndef _SHOPSYSTEM_H_
#define _SHOPSYSTEM_H_ 
#include "cocos2d.h"
#include"editor-support/cocostudio/CCSGUIReader.h"
#include"ui/CocosGUI.h"
#include"cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

class ShopSystem:public Layer{
public:
	CREATE_FUNC(ShopSystem);
	virtual bool init();
	/*UI*/
	Widget* _ui;

	/*touch listener*/
	bool isTouch1;
	void button1Callfunc(Ref*, TouchEventType type);
	bool isTouch2;
	void button2Callfunc(Ref*, TouchEventType type);
	bool isTouch3;
	void button3Callfunc(Ref*, TouchEventType type);
	bool isTouch4;
	void button4Callfunc(Ref*, TouchEventType type);
	bool isTouch5;
	void button5Callfunc(Ref*, TouchEventType type);

	void buttonBackCallfunc(Ref*, TouchEventType type);
};

#endif // !_SHOPSYSTEM_H_