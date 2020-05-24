#ifndef _Weapon_H__
#define _Weapon_H__

#include "cocos2d.h"
USING_NS_CC;

class Weapon :public Node
{
private:
	
public:
	//����ͼ��
	Sprite* weaponSprite;
	//���캯��
	Weapon(int attack,String name);
	//��ʼ��
	virtual bool init();
	//��ͼ��
	void bindSprite();
	//������
	CC_SYNTHESIZE(int, attack, Attack);
	//��������
	String weaponName;
	//��ȡ����ͼ��
	Sprite* getWeapnSprite();
	//����ͼ��
	Vector<SpriteFrame*> weaponSpriteVec;
};


#endif // !_Weapon_H__
