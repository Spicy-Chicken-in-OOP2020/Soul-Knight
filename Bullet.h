#ifndef _BULLET_H__
#define _BULLET_H__

#include "GlobalParameter.h"

class Bullet :public Node
{
private:
	//�ӵ�״̬
	bool isActive;
	//ͼƬ����
	Sprite* bulletSprite;
	//�ӵ��ٶ�
	int speed = 500;

	//����λ��
	int finalX;
	int finalY;

public:
	//���캯��
	Bullet();
	virtual bool init();
	//�����ӵ�
	void shoot(Point position);
	//�����ӵ�״̬
	void setActive(bool _isActive);
	//����ӵ�״̬
	bool getActive();
	//�ж��Ƿ񵽴�Ŀ��
	bool isArrive();
	//��ͼ��
	void bindSprite(Sprite *sprite);
	//���º���
	void update(float dt);
};
#endif // !_BULLET_H__
