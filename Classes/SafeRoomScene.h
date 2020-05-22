#ifndef __SAFEROOMSCENE_H__
#define __SAFEROOMSCENE_H__

#include "Hero.h"

#include "ShootController.h"
#include "GlobalParameter.h"
#include "Monster.h"
#include "SpikeWeed.h"

class SafeRoomScene :public Layer {
public:
	CREATE_FUNC(SafeRoomScene);
	virtual bool init();
	static Scene* createScene();
	Hero* addHero(TMXTiledMap* map);

	/*load UI layer*/
	Layer* mainUiInit(Hero* hero);

private:

	/*Ó¢ÐÛ*/
	Hero* _hero;

	/*µØ´Ì*/
	Vector<SpikeWeed*> spikeList;

public:

};

#endif