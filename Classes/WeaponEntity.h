#ifndef _WEAPON_ENTITY_H__
#define _WEAPON_ENTITY_H__
#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

class WeaponEntity:public Node
{
private:
	//����
	Sprite* sprite;
public:
	//��ͼ��
	void bindSprite(Sprite *sprite)
	{
		this->sprite = sprite;
	}

	Sprite* getSprite()
	{
		return this->sprite;
	}

};


#endif // !_WEAPON_ENTITY_H__
