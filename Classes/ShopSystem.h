#ifndef _TollgateScene_H_
#define _TollgateScene_H_
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;

class TollgateScene:public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void setWareInformation(int i, String name, int price, String ImageFileRoad);
	Text* texts[5];
	Image* images[5];
	Text* price[5];
	Button* buttons[5];
};

#endif // !_TollgateScene_H_

