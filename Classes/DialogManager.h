#ifndef __DialogManager_H__
#define __DialogManager_H__

#include "cocos2d.h"
#include "DialogLayer.h"

class DialogManager :public Node {
public:
	CREATE_FUNC(DialogManager);
	virtual bool init();
	virtual void update(float dt);
	void addDialog(Hero* hero,Node* node);
private:
	Vector<DialogLayer*> dialogList;
};
#endif

