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

class Items:public Node{
private:
	/*精灵*/
	Sprite* _sprite;
public:
	/*constructor*/
	Items();
	~Items();
	/*根据道具编号创建道具*/
	static Items* createItems(int itemsTag);
	CREATE_FUNC(Items);
	virtual bool init();

	/*绑定精灵*/
	Sprite* getSprite();

	/*与人物交互*/
	void keyBoard_k_register();
	virtual void update(float dt);
	/*根据属性选择对人物的作用*/
	void effectOfItems(int itemsTag);
};

#endif // !_ITEMS_H_