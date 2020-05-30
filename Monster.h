#ifndef _MONSTER_H_
#define _MONSTER_H_


#include "cocos2d.h"
#include "Entity.h"
#include "GlobalParameter.h"
#include "Gun.h"
#include "Weapon.h"
#include "Knife.h"

#define DIRECTIONCHANGETIME 1500
#define THINKTIME 500
#define GUN_TAG 1
#define DAO_TAG 2 
USING_NS_CC;

class Monster :public Entity, public ControlListener {
public:
	Monster();
	~Monster();

	CREATE_FUNC(Monster);

	virtual bool init();
	void initWithWeaponTag(int tag);

	virtual void getHurt(int hurtValue) override;
	virtual void attack(Entity* entity) override;
	void unattack();

	Point getPoint();/*取得对象坐标*/
	void move();/*怪物移动*/
	
	void update(float dt);

	//移动状态
	CC_SYNTHESIZE(bool, isMoving, IsMoving);
	

	/*设置武器*/
	void setWeapon(Weapon* weapon);

	/*controllistener*/
	virtual bool setTagPosition(int x, int y)override;;

	virtual Point getTagPosition()override;
	
private:
	/*四个方向*/
	CC_SYNTHESIZE(bool, _up, up);
	CC_SYNTHESIZE(bool, _down, down);
	CC_SYNTHESIZE(bool, _left, left);
	CC_SYNTHESIZE(bool, _right, right);
	/*移动速度*/
	CC_SYNTHESIZE(int, _moveSpeed, moveSpeed);
	MoveTo* _moveTo;
	/*上次是否移动*/
	CC_SYNTHESIZE(Point, _lastPoint, lastPoint);
	bool isNotMove(const Point& lastPoint, const Point& curPoint);

	/*改变方向*/
	void changeDirection();

	virtual void deadResult() override;
	/*攻击范围*/
	float _attackR;

	/*思考时间*/
	int _thinkTime;
	/*武器*/
	Weapon* _weapon;
	int _weaponTag;
	/*障碍层*/
	TMXLayer* _collisionLayer;
	TMXLayer* _collision1Layer;
	TMXLayer* _outsideLayer;
	TMXLayer* _canLayer;

	/*碰撞检测*/
	bool isStuck(const Point& curPos);

	/*出生动画*/
	void birthAnimate();
	/*出生点*/
	Point getBirthPlace();
	void settBirthPlace(const Point& pos);
private:
	/*播放动画*/
	Sprite* _actionSprite;
	/*出生点*/
	Point _birthPlace;
};

#endif // !_MONSTER_H_


