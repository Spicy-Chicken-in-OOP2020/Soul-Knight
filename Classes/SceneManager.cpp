#include "SceneManager.h"
#include "StartScene.h"
#include "HelloWorldScene.h"
#include "SafeRoomScene.h"
#include "testScene.h"
SceneManager* SceneManager::_sceneManager = nullptr;

SceneManager* SceneManager::getInstance() {
	if (!_sceneManager) {
		_sceneManager = new SceneManager();
		if (_sceneManager && _sceneManager->init()) {
			_sceneManager->autorelease();
			_sceneManager->retain();
		}
		else {
			CC_SAFE_DELETE(_sceneManager);
			_sceneManager = nullptr;
		}
	}
	return _sceneManager;
}

bool SceneManager::init() {
	return true;
}

void SceneManager::changeScene(EnumSceneType sceneType) {
	Scene* scene = nullptr;

	switch (sceneType) {
	case StartScene:
		scene = StartScene::createScene();
		break;
	case HelloWorldScene: 
		scene = HelloWorld::createScene();
		break;
	case SafeRoomScene:
		scene = SafeRoomScene::createScene();
		break;
	case WinScene:
		break;
		/*´ýÀ©Õ¹*/
	case testScene:
		scene = testScene::createScene();
		break;
	}

	if (!scene) {
		return;
	}
	Director* pDirector = Director::getInstance();
	Scene* curScene = pDirector->getRunningScene();
	if (!curScene) {
		pDirector->runWithScene(scene);
	}
	else {
		pDirector->replaceScene(scene);
	}
}