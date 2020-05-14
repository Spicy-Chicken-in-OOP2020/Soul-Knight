#ifndef __SAFEROOMSCENE_H__
#define __SAFEROOMSCENE_H__

#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

class SafeRoomScene :public Scene {
public:
	CREATE_FUNC(SafeRoomScene);
	virtual bool init();
	static Scene* createScene();
	Hero* addHero(TMXTiledMap* map);
};

#endif