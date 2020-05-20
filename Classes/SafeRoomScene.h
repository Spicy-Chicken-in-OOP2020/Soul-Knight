#ifndef __SAFEROOMSCENE_H__
#define __SAFEROOMSCENE_H__

#include "Hero.h"
#include "ShootController.h"
#include "GlobalParameter.h"


class SafeRoomScene :public Layer {
public:
	CREATE_FUNC(SafeRoomScene);
	virtual bool init();
	static Scene* createScene();
	Hero* addHero(TMXTiledMap* map);

	Layer* mainUiInit(Hero* hero);
private:

	Hero* _hero;
};

#endif