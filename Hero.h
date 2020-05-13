#ifndef _HERO_H_
#define _HERO_H_
#include "Entity.h"
#include "cocos2d.h"
USING_NS_CC;

class Hero:public Entity {
public:
	Hero();
	~Hero();
	static Hero* create(Sprite* sprite);
	bool init(Sprite* sprite);
	
	/*从Json文件通过id导入英雄配置*/
	static Hero* createFromJsonFile(int modelId);
	bool initFromJsonFileByID(int modelId);

	virtual void attack(Entity* entity);
	virtual void getHurt(int hurtValue);
	virtual void deadResult();
	
	/*捡到药瓶*/
	void addHp();
	void addMp();

	CC_SYNTHESIZE(int, _weapon, weapon);
};

#endif // !_HERO_H_