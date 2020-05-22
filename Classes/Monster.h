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

	void setStartPoint();/*随机设置坐标*/
	Point getPoint();/*取得对象坐标*/
	void move();/*怪物移动*/

	/*是否遇到障碍物*/
	bool isStuck();
	
	void update(float dt);

	//移动状态
	CC_SYNTHESIZE(bool, isMoving, IsMoving);
	/*移动速度*/
	CC_SYNTHESIZE(int,movingSpeed,MovingSpeed);
private:
	virtual void deadResult();

};

#endif // !_MONSTER_H_


