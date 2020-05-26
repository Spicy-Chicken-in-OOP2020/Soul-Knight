#ifndef _TOLLGATEMAPLAYER_H_
#define _TOLLGATEMAPLAYER_H_
#include"cocos2d.h"
USING_NS_CC;

class TollGateMapLayer:public Layer{
public:
	TollGateMapLayer();
	~TollGateMapLayer();

	CREATE_FUNC(TollGateMapLayer);
	virtual bool init();
private:
	/*当前关卡*/
	int curLevel;
	/*读取关卡配置*/
	void loadConfig();
};

#endif // !_TOLLGATEMAPLAYER_H_