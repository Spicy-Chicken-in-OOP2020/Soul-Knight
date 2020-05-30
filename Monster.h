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

	Point getPoint();/*ȡ�ö�������*/
	void move();/*�����ƶ�*/
	
	void update(float dt);

	//�ƶ�״̬
	CC_SYNTHESIZE(bool, isMoving, IsMoving);
	

	/*��������*/
	void setWeapon(Weapon* weapon);

	/*controllistener*/
	virtual bool setTagPosition(int x, int y)override;;

	virtual Point getTagPosition()override;
	
private:
	/*�ĸ�����*/
	CC_SYNTHESIZE(bool, _up, up);
	CC_SYNTHESIZE(bool, _down, down);
	CC_SYNTHESIZE(bool, _left, left);
	CC_SYNTHESIZE(bool, _right, right);
	/*�ƶ��ٶ�*/
	CC_SYNTHESIZE(int, _moveSpeed, moveSpeed);
	MoveTo* _moveTo;
	/*�ϴ��Ƿ��ƶ�*/
	CC_SYNTHESIZE(Point, _lastPoint, lastPoint);
	bool isNotMove(const Point& lastPoint, const Point& curPoint);

	/*�ı䷽��*/
	void changeDirection();

	virtual void deadResult() override;
	/*������Χ*/
	float _attackR;

	/*˼��ʱ��*/
	int _thinkTime;
	/*����*/
	Weapon* _weapon;
	int _weaponTag;
	/*�ϰ���*/
	TMXLayer* _collisionLayer;
	TMXLayer* _collision1Layer;
	TMXLayer* _outsideLayer;
	TMXLayer* _canLayer;

	/*��ײ���*/
	bool isStuck(const Point& curPos);

	/*��������*/
	void birthAnimate();
	/*������*/
	Point getBirthPlace();
	void settBirthPlace(const Point& pos);
private:
	/*���Ŷ���*/
	Sprite* _actionSprite;
	/*������*/
	Point _birthPlace;
};

#endif // !_MONSTER_H_


