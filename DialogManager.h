#ifndef __DialogManager_H__
#define __DialogManager_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Weapon.h"
#include "Items.h"
USING_NS_CC;

class DialogManager :public Layer {
public:
	static Layer* createLayer();
	CREATE_FUNC(DialogManager);
	virtual bool init();

	virtual void update(float dt); 
	bool bindHero(Hero* hero); //绑定主角
	bool addDialog(Weapon* weapon); //增加有台词的物品
	bool addDialog(Node*);
private:
	Hero* _hero;
	Vector<Node*>objectList;
	Map<Node*, Label*> dialogList;
	bool interact(Node* object);
};
#endif

