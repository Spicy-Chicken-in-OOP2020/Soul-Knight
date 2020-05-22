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

/*������������*/
class GlobalParameter
{
public:
	//�洢��ǰ���ڵ�ͼ�ı���
	static TMXTiledMap* mapNow;
	//BGM�Ƿ���
	static bool BGM;
	//SE�Ƿ���
	static bool SE;
	//�������ճ���
	static bool upSide;
	static bool downSide;
	static bool leftSide;
	static bool rightSide;
	//����
	static Hero* hero;
};



#endif // !_GLOBALPARAMETER_H_

