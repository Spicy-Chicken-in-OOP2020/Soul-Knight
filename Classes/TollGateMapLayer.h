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
	/*��ǰ�ؿ�*/
	int curLevel;
	/*��ȡ�ؿ�����*/
	void loadConfig();
};

#endif // !_TOLLGATEMAPLAYER_H_