#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
class GunNormal;

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
private:
	virtual void deadResult();
	/*�ӵ�����*/
	GunNormal* _gun;
};

#endif // !_MONSTER_H_


