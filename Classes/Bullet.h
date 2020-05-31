#ifndef _BULLET_H__
#define _BULLET_H__

#include "GlobalParameter.h"
class Monster;

class Bullet :public Node
{
private:

	//�ӵ�״̬
	bool isActive;
	//ͼƬ����
	Sprite* bulletSprite;
	//��������
	Sprite* actionSprite;
	//�ӵ��ٶ�
	int speed = 500;

	//����λ��
	int finalX;
	int finalY;

	//�ӵ����
	int numBullet;
public:
	//���캯��
	Bullet();//

	Bullet(int numBullet);
	virtual bool init();
	//�����ӵ�
	void shoot(Point position);
	void shootForMonster(Point position,Monster* monster );
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
	//��ð󶨵�ͼ��
	Sprite* getBindSprite();

	
};
#endif // !_BULLET_H__
