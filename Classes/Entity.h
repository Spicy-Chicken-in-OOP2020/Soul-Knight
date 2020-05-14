#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node {
public:
	Entity();
	~Entity();

	void bindSprite(Sprite* sprite);		/*绑定对象*/
	Sprite* getSprite();

	bool isDead();							/*是否死亡*/

	virtual void attack(Entity* entity) = 0;/*攻击*/
	virtual void getHurt(int hurtValue) = 0;/*遭到攻击*/

protected:
	Sprite* _sprite;
	bool _isDead;


	virtual void deadResult() = 0;			/*死亡时调用*/

	CC_SYNTHESIZE(int, _modelId, modelId);  /*Json文件英雄id*/
	CC_SYNTHESIZE(int, _hp, hp);			/*生命值*/
	CC_SYNTHESIZE(int, _hpMax, hpMax);		/*生命值上限*/
	CC_SYNTHESIZE(int, _defense, defense);	/*防御力*/
	CC_SYNTHESIZE(int, _defenseMax, defenseMax);		/*防御力上限*/
	CC_SYNTHESIZE(int, _mp, mp);			/*魔法值*/
	CC_SYNTHESIZE(int, _mpMax, mpMax);		/*魔力值上限*/
	CC_SYNTHESIZE(int, _attack, attack);    /*攻击力*/
};

#endif // !_ENTITY_H_