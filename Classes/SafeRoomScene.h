#ifndef __SAFEROOMSCENE_H__
#define __SAFEROOMSCENE_H__

#include "Hero.h"
#include "MonsterManager.h"
#include "ShootController.h"
#include "GlobalParameter.h"
#include "PauseLayer.h"
#include "SpikeWeed.h"

class SafeRoomScene :public Scene {
public:
	CREATE_FUNC(SafeRoomScene);
	virtual bool init();
	static Scene* createScene();
	Hero* addHero(TMXTiledMap* map,Layer* layer);

	/*load UI layer*/
	Layer* mainUiInit(Hero* hero);
	/*��ӵ�ͼ��*/
	void addMap();
	/*��ͣ��ť�ص�*/
	void pauseButton(Ref*, TouchEventType type);

	static TMXTiledMap* _safeRoomMap;

	/*Ӣ��*/
	static Hero* _hero;
	/*��ͣ����*/
	static PauseLayer* _pauseLayer;
	/*����*/
	static SafeRoomScene* _safeRoomScene;

	/*���������*/
	static MonsterManager* _monsterManager;

	/*�ش�*/
	Vector< SpikeWeed*> _spikeList;

};

#endif