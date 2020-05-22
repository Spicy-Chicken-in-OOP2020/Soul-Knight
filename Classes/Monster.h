#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "GlobalParameter.h"

USING_NS_CC;

class Monster :public Entity {
	const static int _moveDirSpeed[4][2];
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();

	virtual void getHurt(int hurtValue);
	virtual void attack(Entity* entity);

	void setStartPoint();/*�����������*/
	Point getPoint();/*ȡ�ö�������*/
	void move();/*�����ƶ�*/

	/*�Ƿ������ϰ���*/
	bool isStuck();
	
	void update(float dt);

	//�ƶ�״̬
	CC_SYNTHESIZE(bool, isMoving, IsMoving);
	/*�ƶ��ٶ�*/
	CC_SYNTHESIZE(int,movingSpeed,MovingSpeed);
private:
	virtual void deadResult();

};

#endif // !_MONSTER_H_


