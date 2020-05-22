#ifndef _SpikeWeed_H__
#define _SpikeWeed_H__
#include "GlobalParameter.h"

class SpikeWeed :public Node
{
private:
	//�ش�ͼ��
	Sprite* spikeSprite;
	//ͼƬ��Դ
	Vector<SpriteFrame*> frameVec;
	//������Դ

public:
	//���캯��
	SpikeWeed();
	//��������
	~SpikeWeed();
	//��ʼ��
	virtual bool init();
	//�趨ͼ��
	void setSprite();
	//�ش̸ı�ʱ��
	CC_SYNTHESIZE(double, changeTime, ChangeTime);
	//�ش��Ƿ�չ��
	CC_SYNTHESIZE(bool, isStabbing, IsStabbing);
	//�ش̸ı���̬
	void spikeUpdate(float dt);
	//����Ƿ������Ƿ�����ײ
	void update(float dt);
};


#endif // !_SpikeWeed_H__
