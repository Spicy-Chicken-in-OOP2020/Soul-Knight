#ifndef _BULLET_BASE_H__
#define _BULLET_BASE_H__
#include "WeaponEntity.h"
#pragma once
class BulletBase:public WeaponEntity
{
public:
	//构造函数
	BulletBase();
	//析构函数
	~BulletBase();

	//是否到达攻击目标
	bool isArrive();

	//是否正在使用
	void setUsed(bool isUsed);
	bool isUsed();
private:
	//是否正在使用中
	bool m_isUsed;

	bool m_isArrive;//是否到达了攻击目标

	//攻击力
	CC_SYNTHESIZE(int, m_isAtkValue, iAtkValue);
	//速度
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
	//坐标位置
	CC_SYNTHESIZE(Point, m_Position, bulletPosition);

private:

};


#endif // !_BULLET_BASE_H__
