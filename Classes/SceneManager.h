#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;

class SceneManager:public Ref{
public:
	/*����ö��*/
	enum EnumSceneType {
		StartScene,
		HelloWorldScene,
		SafeRoomScene,
		TollgateScene,
		WinScene,
		testScene
	};

	/*��ȡ��������������,������*/
	static SceneManager* getInstance();

	virtual bool init();

	void changeScene(EnumSceneType sceneType);

private:
	/*��������������*/
	static SceneManager* _sceneManager;
};

#endif // !_SCENEMANAGER_H_