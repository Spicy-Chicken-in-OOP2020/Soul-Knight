#include "TollgateScene.h"
#include "TollGateMapLayer.h"
Scene* TollgateScene::createScene() {
	Scene* scene = Scene::create();

	TollgateScene* tollgateScene = TollgateScene::create();
	scene->addChild(tollgateScene, 3);

	TollGateMapLayer* tollGateMapLayer = TollGateMapLayer::create();
	scene->addChild(tollGateMapLayer, 1,TAG_MAP_LAYER);

	return scene;
}

bool TollgateScene::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}