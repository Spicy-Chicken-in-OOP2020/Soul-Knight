#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;

class SceneManager:public Ref{
public:
	/*场景枚举*/
	enum EnumSceneType {
		StartScene,
		HelloWorldScene,
		SafeRoomScene,
		TollgateScene,
		WinScene,
		testScene
	};

	/*获取场景管理器对象,单例类*/
	static SceneManager* getInstance();

	virtual bool init();

	void changeScene(EnumSceneType sceneType);

private:
	/*场景管理器对象*/
	static SceneManager* _sceneManager;
};

#endif // !_SCENEMANAGER_H_