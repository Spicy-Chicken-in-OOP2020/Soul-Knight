#include "BulletNormal.h"

BulletNormal::BulletNormal()
{
	//ËÙ¶È
	m_iSpeed = 1;
}

BulletNormal::~BulletNormal()
{

}

BulletNormal* BulletNormal::create(Sprite* sprite)
{
	BulletNormal* bulletNor = new BulletNormal();
	if (bulletNor && bulletNor->init(sprite))
	{
		bulletNor->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bulletNor);
	}
	return bulletNor;
}

bool BulletNormal::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

bool BulletNormal::init()
{
	bool bRet = false;
	do
	{
		//×Óµ¯Í¼Æ¬
		Sprite* sprite = Sprite::create("bullet\bullet6");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	return bRet;
}