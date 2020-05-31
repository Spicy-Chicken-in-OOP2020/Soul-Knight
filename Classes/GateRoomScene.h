#ifndef __GATEROOMSCENE_H__
#define __GATEROOMSCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "PauseLayer.h"
USING_NS_CC;

class GateRoomScene :public Layer {
public:


	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(GateRoomScene);
	
	//void bindHero(Hero* _hero);   //为当前的场景绑定一个已经设置好的hero;
	void bindCurGateRoomMap(TMXTiledMap* map); //绑定当前的场景关卡地图;
	//void registeKeyBoardEvent();  //关卡地图内的键盘监听事件;
	//Point getHeroPos();         //获得当前英雄的坐标;
	//bool canBeTransmitted();
	//Hero* GateRoomScene::addHero(TMXTiledMap* map);
	//void bindPortal();

private:
	/*Hero* _hero;*/
	TMXTiledMap* curGateRoomMap; 
	//Point tileCoordForPosition(Point pos); //目的是为了转换坐标 地图的像素坐标转化成地图格子坐标);
	//static int curNum;  //当前第几大关;
	//static int curGate; //当前第几幅图;
	//static PauseLayer* _pauseLayer; //暂停界面;
};

#endif
