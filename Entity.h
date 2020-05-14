#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node {
public:
	Entity();
	~Entity();

	void bindSprite(Sprite* sprite);		/*�󶨶���*/
	Sprite* getSprite();

	bool isDead();							/*�Ƿ�����*/

	virtual void attack(Entity* entity) = 0;/*����*/
	virtual void getHurt(int hurtValue) = 0;/*�⵽����*/

protected:
	Sprite* _sprite;
	bool _isDead;


	virtual void deadResult() = 0;			/*����ʱ����*/

	CC_SYNTHESIZE(int, _modelId, modelId);  /*Json�ļ�Ӣ��id*/
	CC_SYNTHESIZE(int, _hp, hp);			/*����ֵ*/
	CC_SYNTHESIZE(int, _hpMax, hpMax);		/*����ֵ����*/
	CC_SYNTHESIZE(int, _defense, defense);	/*������*/
	CC_SYNTHESIZE(int, _defenseMax, defenseMax);		/*����������*/
	CC_SYNTHESIZE(int, _mp, mp);			/*ħ��ֵ*/
	CC_SYNTHESIZE(int, _mpMax, mpMax);		/*ħ��ֵ����*/
	CC_SYNTHESIZE(int, _attack, attack);    /*������*/
};

#endif // !_ENTITY_H_