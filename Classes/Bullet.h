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
	//子弹速度
	int speed = 500;

	//最终位置
	int finalX;
	int finalY;

public:
	//构造函数
	Bullet();
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
};
#endif // !_BULLET_H__
