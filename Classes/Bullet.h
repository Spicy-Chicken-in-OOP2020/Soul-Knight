#ifndef _BULLET_H__
#define _BULLET_H__

#include "cocos2d.h"
USING_NS_CC;
class Bullet :public Node
{
public:
	bool isActive;//当前是否被使用
	Sprite* bullet;//图片
	int speed;
	void shoot(Point position);//发射子弹
	static Bullet* createBullet(Point position);
	void bulletInit(Point position);
	static Scene* createScene();
	virtual bool init();
	void setActive(bool _isActive);
	//判定是否到达目标
	bool isArrive();
	CREATE_FUNC(Bullet);
	//获取射击方向
	int leftSpeed;
	int rightSpeed;
	int upSpeed;
	int downSpeed;
};
#endif // !_BULLET_H__
