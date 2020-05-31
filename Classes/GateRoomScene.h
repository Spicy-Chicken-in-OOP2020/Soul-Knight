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
	
	//void bindHero(Hero* _hero);   //Ϊ��ǰ�ĳ�����һ���Ѿ����úõ�hero;
	void bindCurGateRoomMap(TMXTiledMap* map); //�󶨵�ǰ�ĳ����ؿ���ͼ;
	//void registeKeyBoardEvent();  //�ؿ���ͼ�ڵļ��̼����¼�;
	//Point getHeroPos();         //��õ�ǰӢ�۵�����;
	//bool canBeTransmitted();
	//Hero* GateRoomScene::addHero(TMXTiledMap* map);
	//void bindPortal();

private:
	/*Hero* _hero;*/
	TMXTiledMap* curGateRoomMap; 
	//Point tileCoordForPosition(Point pos); //Ŀ����Ϊ��ת������ ��ͼ����������ת���ɵ�ͼ��������);
	//static int curNum;  //��ǰ�ڼ����;
	//static int curGate; //��ǰ�ڼ���ͼ;
	//static PauseLayer* _pauseLayer; //��ͣ����;
};

#endif
