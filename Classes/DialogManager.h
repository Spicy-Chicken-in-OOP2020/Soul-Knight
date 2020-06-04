#ifndef __DialogManager_H__
#define __DialogManager_H__

#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

class DialogManager :public Node {
public:
	CREATE_FUNC(DialogManager);
	static Scene* createDialog(const Vec2& pos,std::string,bool needDisappear);
	virtual bool init();
private:
	void registeKeyBoardEvent();
};
#endif // !__DialogManager_H__
