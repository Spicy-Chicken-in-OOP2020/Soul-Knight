#ifndef __CONTROLLISTENER_H__
#define __CONTROLLISTENER_H__

#include"cocos2d.h"

USING_NS_CC;

class ControlListener {
public:
	virtual void setTagPosition(int x, int y) = 0;

	virtual Point getTagPosition() = 0;
};


#endif