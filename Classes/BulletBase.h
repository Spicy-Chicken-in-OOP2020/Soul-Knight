#ifndef _BULLET_BASE_H__
#define _BULLET_BASE_H__
#include "WeaponEntity.h"
#pragma once
class BulletBase:public WeaponEntity
{
public:
	//���캯��
	BulletBase();
	//��������
	~BulletBase();

	//�Ƿ񵽴﹥��Ŀ��
	bool isArrive();

	//�Ƿ�����ʹ��
	void setUsed(bool isUsed);
	bool isUsed();
private:
	//�Ƿ�����ʹ����
	bool m_isUsed;

	bool m_isArrive;//�Ƿ񵽴��˹���Ŀ��

	//������
	CC_SYNTHESIZE(int, m_isAtkValue, iAtkValue);
	//�ٶ�
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
	//����λ��
	CC_SYNTHESIZE(Point, m_Position, bulletPosition);

private:

};


#endif // !_BULLET_BASE_H__
