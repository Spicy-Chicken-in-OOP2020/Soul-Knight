#ifndef _HERO_H_
#define _HERO_H_
#include "Entity.h"
#include "cocos2d.h"
#include "GameController.h"
#include "ControlListener.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "GlobalParameter.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;


class Hero :public Entity, public ControlListener {
public:
	Hero();
	~Hero();
	static Hero* create(Sprite* sprite);
	bool init(Sprite* sprite);

	/*��Json�ļ�ͨ��id����Ӣ������*/
	static Hero* createFromJsonFile(int modelId);
	bool initFromJsonFileByID(int modelId);

	/*�󶨿�����*/
	void setController(GameController* gameController, GameController* shotController);
	/*��ȡ������*/
	GameController* getMoveController();


	/* ControlListener�ӿڷ���ʵ��*/
	virtual bool setTagPosition(int x, int y);
	virtual Point getTagPosition();
	void setViewPointByHero();
	void setSafeRoomTiledMap(TMXTiledMap* map);
	
	/*��Ϊ*/
	virtual void attack(Entity* entity);
	virtual void getHurt(int hurtValue);
	virtual void deadResult();

	/*Ѫ��������������������*/
	void bindHp(LoadingBar* hpBar,Label* hpLabel,Label* hpMaxLabel);
	void bindMp(LoadingBar* mpBar,Label* mpLabel,Label* mpMaxLabel);
	void bindDefense(LoadingBar* defenseBar,Label* defenseLabel,Label* defenseMaxLabel);


	/*Ҳ�����ڳ�ʼ��*/
	void setHp(int hpValue);
	void setMp(int mpValue);
	void setDefense(int defenseValue);
	/*����*/
	CC_SYNTHESIZE(int, _weapon, weapon);
private:
	GameController* _gameController;
	GameController* _shotController;
	TMXTiledMap* _safeRoomMap;

	/*UI������*/
	LoadingBar* _hpLoadingBar;
	LoadingBar* _mpLoadingBar;
	LoadingBar* _defenseLoadingBar;

	/*UI��ֵ*/
	Label* _hpLabel;
	Label* _hpMaxLabel;
	Label* _defenseLabel;
	Label* _defenseMaxLabel;
	Label* _mpLabel;
	Label* _mpMaxLabel;

	/*��������*/
	bool isStuck;
	
};

#endif // !_HERO_H_