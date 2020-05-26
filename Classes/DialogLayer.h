#ifndef __DialogLayer_H__
#define __DialogLayer_H__

#include "cocos2d.h"
#include "Hero.h"
#include <string.h>
USING_NS_CC;

class DialogLayer :public Layer {
public:
	static Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(DialogLayer);

	bool bindHero(Hero* hero);  //绑定主角
	bool bindObject(Node* object);  //绑定对话对象
	virtual void update(float delta);
	bool getShowState();
private:
	Hero* m_hero;
	Node* m_object;
	Label* label;
	bool needToShow;
};
#endif // !__DialogLayer_H__

