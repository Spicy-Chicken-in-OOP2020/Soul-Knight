#ifndef _TOLLGATESCENE_H_
#define _TOLLGATESCENE_H_
#include"cocos2d.h"
#include"Monster.h"
#include"Hero.h"
USING_NS_CC;
#define MAP ".\\soul_knight_%d_%d\\soul_knight_%d_%d.tmx"
//#define MAP "soul_knight_%d_%d.tmx"

class TollgateScene:public Scene{
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();

	Hero* addHero(TMXTiledMap* map, Layer* layer);

private:
	/*¹Ø¿¨µØÍ¼*/
	TMXTiledMap* _tollgateMap;
	void addMap();
	Hero* _hero;

};

#endif // !_TOLLGATESCENE_H_