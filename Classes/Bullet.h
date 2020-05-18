#ifndef _BULLET_H__
#define _BULLET_H__

#include "cocos2d.h"
USING_NS_CC;
class Bullet :public Node
{
public:
	bool isActive;//��ǰ�Ƿ�ʹ��
	Sprite* bullet;//ͼƬ
	int speed;
	void shoot(Point position);//�����ӵ�
	static Bullet* createBullet(Point position);
	void bulletInit(Point position);
	static Scene* createScene();
	virtual bool init();
	void setActive(bool _isActive);
	//�ж��Ƿ񵽴�Ŀ��
	bool isArrive();
	CREATE_FUNC(Bullet);
	//��ȡ�������
	int leftSpeed;
	int rightSpeed;
	int upSpeed;
	int downSpeed;
};
#endif // !_BULLET_H__
