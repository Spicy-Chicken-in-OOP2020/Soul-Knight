#ifndef __PauseLayer_H__
#define __PauseLayer_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;

class PauseLayer :public Layer {
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	void settingSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void BGmusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void effectMusicSelectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void homeEvent(Ref*, TouchEventType type);
	void resumeEvent(Ref*, TouchEventType type);
	bool BGmusic();  //�жϱ��������Ƿ���
	bool effectMusic();  //�ж���Ч�ܷ���
	void setHeroHead(Sprite* heroHead);
	void setBuff(Sprite* buff,int i);

	/*��ͣ����*/
	static PauseLayer* _pauseLayer;
	static PauseLayer* createPauseLayer();
private:
	bool isBGmusicplaying;
	bool isEffecMusicTurnOn;
	CheckBox* Btn_BGmusic;
	CheckBox* Btn_effectMusic;
	Sprite* m_heroHead;
	Vector<Sprite*> m_buff;
};
#endif // !__PauseLayer_H__

