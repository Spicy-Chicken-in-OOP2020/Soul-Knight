#ifndef _HERO_H_
#define _HERO_H_
#include "Entity.h"
#include "cocos2d.h"
#include "GameController.h"
#include "ControlListener.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "GlobalParameter.h"
#include "Gun.h"
#include "ShootController.h"

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
	void setController(GameController* gameController);
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
	void setHpMax(int hpMaxValue);
	void setMpMax(int mpMaxValue);
	void setDefenseMax(int defenseMaxValue);

	/*����*/
	Weapon* weapon;

	/*��ʱ��*/
	void defenseAutoAdd(float dt);

	//��������
	void setWeapon(Weapon* weapon);
	//�Ƴ���ǰ����
	Weapon* removeWeapon();

	//�������ǳ���
	void setHeroRun(bool rightSide);
	void setHeroStill(bool rightSide);

	//����������ʽ
	void update(float dt);

	//�������˵�����ͼ
	Vector<SpriteFrame*> leftSpriteVec, rightSpriteVec;

private:
	GameController* _gameController;
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
	
	/*���ܻظ��ٶ�*/
	float defenseRecoverSpeed;
};

#endif // !_HERO_H_