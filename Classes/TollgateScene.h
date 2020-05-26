#ifndef _TOLLGATESCENE_H_
#define _TOLLGATESCENE_H_
#include"cocos2d.h"
USING_NS_CC;
#define TAG_MAP_LAYER 1

class TollgateScene:public Layer{
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
};

#endif // !_TOLLGATESCENE_H_