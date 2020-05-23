#ifndef __SAFEROOMSCENE_H__
#define __SAFEROOMSCENE_H__

#include "Hero.h"
#include "MonsterManager.h"
#include "ShootController.h"
#include "GlobalParameter.h"
#include "PauseLayer.h"

class SafeRoomScene :public Scene {
public:
	CREATE_FUNC(SafeRoomScene);
	virtual bool init();
	static Scene* createScene();
	Hero* addHero(TMXTiledMap* map,Layer* layer);

	/*load UI layer*/
	Layer* mainUiInit(Hero* hero);
	/*添加地图层*/
	void addMap();
	/*暂停按钮回调*/
	void pauseButton(Ref*, TouchEventType type);

private:

	/*英雄*/
	Hero* _hero;
	/*暂停界面*/
	static PauseLayer* _pauseLayer;
	/*场景*/
	static SafeRoomScene* _safeRoomScene;

public:
	/*怪物管理器*/
	static MonsterManager* _monsterManager;


};

#endif