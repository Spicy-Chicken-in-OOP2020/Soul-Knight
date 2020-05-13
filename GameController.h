#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include"ControlListener.h"
#include"cocos2d.h"

USING_NS_CC;

class GameController :public Node {
public:
	void setMyControlListener(ControlListener* _controlListener);
protected:
	ControlListener* MyControlListener;
};

#endif