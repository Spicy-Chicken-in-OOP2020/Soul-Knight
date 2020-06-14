#ifndef _BULLET_H__
#define _BULLET_H__

#include "GlobalParameter.h"
class Monster;
#define CIRCULE 99
#define SQUARE 98
#define CIRCULENUM 16
#define SQUARENUM 12
#define PI 3.1415926535898
#define SPEED 40
#define R 10000
class Boss;

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

	
public:
	/*Boss*/
	Bullet(int tag,int );
	bool initForBoss();
	void shootBossBullet(const Point& pos,Boss* boss);
};
#endif // !_BULLET_H__
