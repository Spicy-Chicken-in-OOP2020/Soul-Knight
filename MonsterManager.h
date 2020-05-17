#ifndef _MONSTERMANAGER_H_
#define _MONSTERMANAGER_H_
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

#define FRESH_TIMES 4/*敌人刷新波数*/
#define MONSTER_NUM 8/*每次刷新敌人数量*/


class MonsterManager:public Node{
public:
	MonsterManager();
	~MonsterManager();

	/*根据关卡创建怪物管理器*/
	static MonsterManager* createMonsterManagerWithLevel(int curLevel);
	bool initWithLevel(int curlevel);

	void createMonsters(int curLevel);/*创建怪物*/

	Vector<Monster*> getMonsterList();/*获取怪物列表*/
private:
	/*怪物波数*/
	int _monsterTimes;

	Vector<Monster*> _monsterList;/*怪物列表*/

	void showMonster(float dt);/*检查是否有新怪物出场*/
};


#endif // !_MONSTERMANAGER_H_
