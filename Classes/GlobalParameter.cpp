#include"GlobalParameter.h"

/*静态成员变量的初始化*/
TMXTiledMap* GlobalParameter::mapNow = nullptr;
bool GlobalParameter::BGM = true;
bool GlobalParameter::SE = true;
bool GlobalParameter::upSide = false;
bool GlobalParameter::downSide = true;//初始需要有一个朝向
bool GlobalParameter::leftSide = false;
bool GlobalParameter::rightSide = false;

//人物图像最后的相对朝向（为了人物图）
bool GlobalParameter::imageRightSide = true;
bool GlobalParameter::imageLeftSide = false;

Hero* GlobalParameter::hero = nullptr;
