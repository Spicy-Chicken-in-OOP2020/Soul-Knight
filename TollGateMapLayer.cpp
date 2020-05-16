#include "TollGateMapLayer.h"
TollGateMapLayer::TollGateMapLayer() :curLevel(1) {

}

TollGateMapLayer::~TollGateMapLayer() = default;

bool TollGateMapLayer::init() {
	loadConfig();
	
	return true;
}

void TollGateMapLayer::loadConfig() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*To DO »Á±≥æ∞“Ù¿÷°¢µÿÕºµ»*/

}