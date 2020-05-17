#ifndef _MONSTERMANAGER_H_
#define _MONSTERMANAGER_H_
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

#define FRESH_TIMES 4/*����ˢ�²���*/
#define MONSTER_NUM 8/*ÿ��ˢ�µ�������*/


class MonsterManager:public Node{
public:
	MonsterManager();
	~MonsterManager();

	/*���ݹؿ��������������*/
	static MonsterManager* createMonsterManagerWithLevel(int curLevel);
	bool initWithLevel(int curlevel);

	void createMonsters(int curLevel);/*��������*/

	Vector<Monster*> getMonsterList();/*��ȡ�����б�*/
private:
	/*���ﲨ��*/
	int _monsterTimes;

	Vector<Monster*> _monsterList;/*�����б�*/

	void showMonster(float dt);/*����Ƿ����¹������*/
};


#endif // !_MONSTERMANAGER_H_
