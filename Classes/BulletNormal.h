#ifndef _NORMAL_BULLET_H__
#define _NORMAL_BULLET_H__

#include "BulletBase.h"
class BulletNormal:public BulletBase 
{
public:
	BulletNormal();
	~BulletNormal();

	CREATE_FUNC(BulletNormal);
	virtual bool init();

	static BulletNormal* create(Sprite* sprite);
	bool init(Sprite* sprite);

private:
	void moveEnd();
};

#endif // !_NORMAL_BULLET_H__

