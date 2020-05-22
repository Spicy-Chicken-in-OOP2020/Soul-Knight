#ifndef _SpikeWeed_H__
#define _SpikeWeed_H__
#include "GlobalParameter.h"

class SpikeWeed :public Node
{
private:
	//地刺图像
	Sprite* spikeSprite;
	//图片资源
	Vector<SpriteFrame*> frameVec;
	//动画资源

public:
	//构造函数
	SpikeWeed();
	//析构函数
	~SpikeWeed();
	//初始化
	virtual bool init();
	//设定图像
	void setSprite();
	//地刺改变时间
	CC_SYNTHESIZE(double, changeTime, ChangeTime);
	//地刺是否展开
	CC_SYNTHESIZE(bool, isStabbing, IsStabbing);
	//地刺改变形态
	void spikeUpdate(float dt);
	//检测是否与主角发生碰撞
	void update(float dt);
};


#endif // !_SpikeWeed_H__
