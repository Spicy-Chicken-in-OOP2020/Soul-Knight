#ifndef _ITEMS_H_
#define _ITEMS_H_
#include "cocos2d.h"
USING_NS_CC;
#define HP_ADD_TAG 1
#define HP_ADD_NUM 2
#define MP_ADD_TAG 2
#define MP_ADD_NUM 60
#define BS_TAG 3
#define BS_ADD_NUM 1
#define JB_TAG 4
#define JB_ADD_NUM 1
#define KNIFE_TAG 5
#define GUN_TAG 6
#define QUICKGUN_TAG 7

class Items:public Node{
private:
	/*����*/
	Sprite* _sprite;
	/*������ǰ����*/
	void throwWeapon();
public:
	/*constructor*/
	Items();
	~Items();
	/*���ݵ��߱�Ŵ�������*/
	static Items* createItems(int itemsTag, Point position);
	CREATE_FUNC(Items);
	virtual bool init();

	/*�󶨾���*/
	Sprite* getSprite();

	/*�����ｻ��*/
	void keyBoard_k_register();
	virtual void update(float dt);
	/*��������ѡ������������*/
	void effectOfItems(int itemsTag);
};

#endif // !_ITEMS_H_