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

	bool bindHero(Hero* hero);  //������
	bool bindObject(Node* object);  //�󶨶Ի�����
	virtual void update(float delta);
	bool getShowState();
private:
	Hero* m_hero;
	Node* m_object;
	Label* label;
	bool needToShow;
};
#endif // !__DialogLayer_H__

