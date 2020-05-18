#ifndef _BULLET_MANAGER_H__
#define _BULLET_MANAGER_H__

constexpr auto BULLET_MAX_CACHE_NUM = 50; //�ӵ������������

#include "BulletBase.h"
#include "BulletNormal.h"

class BulletManager:public Node
{
public:
	BulletManager();
	~BulletManager();
	static BulletManager* create();
	bool init();

	//�ӻ����л�ȡһ��δ��ʹ�õ��ӵ�
	BulletBase* getAnyUnUsedBullet();
private:
	Vector<BulletBase*> m_bulletList;//�ӵ��б�
	void createBullets(Node* parent);//���������ӵ�
	void bulletLogicCheck(float dt);//�ӵ��߼�
};

#endif // !_BULLET_MANAGER_H__

