#ifndef _HERO_H_
#define _HERO_H_
#include "Entity.h"
#include "cocos2d.h"
#include "GameController.h"
#include "ControlListener.h"
USING_NS_CC;

class Hero :public Entity, public ControlListener{
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

	/*绑定控制器*/
	void setController(GameController* movecontroller);

	/* ControlListener接口方法实现*/
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();
private:
	GameController* _gameController;
};

#endif // !_HERO_H_