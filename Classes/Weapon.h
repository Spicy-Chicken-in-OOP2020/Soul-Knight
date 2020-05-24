#ifndef _Weapon_H__
#define _Weapon_H__

#include "cocos2d.h"
USING_NS_CC;

class Weapon :public Node
{
private:
	
public:
	//武器图像
	Sprite* weaponSprite;
	//构造函数
	Weapon(int attack,String name);
	//初始化
	virtual bool init();
	//绑定图像
	void bindSprite();
	//攻击力
	CC_SYNTHESIZE(int, attack, Attack);
	//武器名称
	String weaponName;
	//获取武器图像
	Sprite* getWeapnSprite();
	//武器图像
	Vector<SpriteFrame*> weaponSpriteVec;
};


#endif // !_Weapon_H__
