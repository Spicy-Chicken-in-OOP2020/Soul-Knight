#ifndef _BULLET_H__
#define _BULLET_H__

#include "GlobalParameter.h"

class Bullet :public Node
{
private:
	//子弹状态
	bool isActive;
	//图片对象
	Sprite* bulletSprite;
	//动画对象
	Sprite* actionSprite;
	//子弹速度
	int speed = 500;

	//最终位置
	int finalX;
	int finalY;

public:
	//构造函数
	Bullet(int numBullet);
	virtual bool init();
	//发射子弹
	void shoot(Point position);
	//设置子弹状态
	void setActive(bool _isActive);
	//获得子弹状态
	bool getActive();
	//判定是否到达目标
	bool isArrive();
	//绑定图像
	void bindSprite(Sprite *sprite);
	//更新函数
	void update(float dt);
	//获得绑定的图像
	Sprite* getBindSprite();
	//子弹编号
	int numBullet;
};
#endif // !_BULLET_H__
