#ifndef _GLOBALPARAMETER_H_
#define _GLOBALPARAMETER_H_

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "Hero.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;

class Hero;

/*公共变量定义*/
class GlobalParameter
{
public:
	//存储当前所在地图的变量
	static TMXTiledMap* mapNow;
	//BGM是否开启
	static bool BGM;
	//SE是否开启
	static bool SE;
	//人物最终朝向
	static bool upSide;
	static bool downSide;
	static bool leftSide;
	static bool rightSide;
	//主角
	static Hero* hero;
};



#endif // !_GLOBALPARAMETER_H_

