#ifndef _HIT_CONTROLLER_H__
#define _HIT_CONTROLLER_H__
#include "GameController.h"
#include "GlobalParameter.h"
#define MAX_IMAGE_SPRITE_NUM 10

class HitController :public GameController
{
public:
	CREATE_FUNC(HitController);
	virtual bool init();
	void hitUpdate(float dt);
	void hitUpdateForMonster(float dt);

	bool isHit;
	//�������Ŷ�����image����
	Sprite* actionSpriteVec[MAX_IMAGE_SPRITE_NUM];
	//�洢image�����Ƿ����ڱ�ʹ��
	bool actionSpriteRun[MAX_IMAGE_SPRITE_NUM];

	static HitController* createForMonster();
	bool initForMonsters();
	void setIsHit(bool isShot);
	
private:
	void registeKeyBoardEvent();
	

};


#endif // !_HIT_CONTROLLER_H__
