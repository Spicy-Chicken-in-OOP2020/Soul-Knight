#include"GlobalParameter.h"

/*��̬��Ա�����ĳ�ʼ��*/
TMXTiledMap* GlobalParameter::mapNow = nullptr;
bool GlobalParameter::BGM = true;
bool GlobalParameter::SE = true;
bool GlobalParameter::upSide = false;
bool GlobalParameter::downSide = true;//��ʼ��Ҫ��һ������
bool GlobalParameter::leftSide = false;
bool GlobalParameter::rightSide = false;

//����ͼ��������Գ���Ϊ������ͼ��
bool GlobalParameter::imageRightSide = true;
bool GlobalParameter::imageLeftSide = false;

Hero* GlobalParameter::hero = nullptr;
