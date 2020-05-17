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

	void setStartPoint();/*随机设置坐标*/
	Point getPoint();/*取得对象坐标*/
	void move();/*怪物移动*/
private:
	virtual void deadResult();
	/*子弹类型*/
	GunNormal* _gun;
};

#endif // !_MONSTER_H_


