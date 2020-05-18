#ifndef _BULLET_MANAGER_H__
#define _BULLET_MANAGER_H__

constexpr auto BULLET_MAX_CACHE_NUM = 50; //子弹缓存最大数量

#include "BulletBase.h"
#include "BulletNormal.h"

class BulletManager:public Node
{
public:
	BulletManager();
	~BulletManager();
	static BulletManager* create();
	bool init();

	//从缓存中获取一个未被使用的子弹
	BulletBase* getAnyUnUsedBullet();
private:
	Vector<BulletBase*> m_bulletList;//子弹列表
	void createBullets(Node* parent);//创建缓存子弹
	void bulletLogicCheck(float dt);//子弹逻辑
};

#endif // !_BULLET_MANAGER_H__

