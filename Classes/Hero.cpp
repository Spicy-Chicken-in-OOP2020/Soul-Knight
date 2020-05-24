#include "Hero.h"
#include "Knife.h"
#include<typeinfo>
Hero::Hero() :weapon(nullptr)
{
	//设定初值
	this->sethp(6);
	this->sethpMax(6);
	this->setmp(6);
	this->setmpMax(6);
	this->setdefense(6);
	this->setdefenseMax(6);
	this->defenseRecoverSpeed = 5;
}

Hero::~Hero() = default;

Hero* Hero::create(Sprite * sprite) {
	Hero* hero = new Hero();
	if (hero && hero->init(sprite))
		hero->autorelease();
	else
		CC_SAFE_DELETE(hero);
	return hero;
}

bool Hero::init(Sprite * sprite) {
	if (!sprite)
		return false;

	//绑定图像
	this->bindSprite(sprite);

	//护盾事件
	this->schedule(schedule_selector(Hero::defenseAutoAdd), this->defenseRecoverSpeed);
	//武器图
	this->scheduleUpdate();

	//尝试直接加载
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Knight1.plist", "Knight1.png");

	int iFrameNum = 3;
	SpriteFrame* frame = NULL;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Knight1Right%d.png", i));
		rightSpriteVec.pushBack(frame);
	}

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Knight1Left%d.png", i));
		leftSpriteVec.pushBack(frame);
	}

	this->_sprite->setSpriteFrame(*(rightSpriteVec.begin() + 1));

	

	return true;
}

void Hero::setController(GameController* gameController) {
	_gameController = gameController;
	_gameController->setMyControlListener(this);
	this->addChild(gameController);
}

bool Hero::setTagPosition(int x, int y) {
	/*在这里需要判断能否更新坐标位置*/
	//获得当前物体坐标

	//判断是否触及障碍物
	Size mapSize = GlobalParameter::mapNow->getMapSize();
	Size tileSize = GlobalParameter::mapNow->getTileSize();

	//读取当前所在地图的障碍物层
	TMXLayer* collisionLayer = GlobalParameter::mapNow->getLayer("collision");

	//获得坐标在地图中的格子位置
	Point tiledPos(x / tileSize.width, (mapSize.height*tileSize.height - y) / tileSize.height);
	
	if (x < 0)
	{
		//迷之报错，在这里隐藏掉
		log("What's wrong with you?");
		return false;
	}

	//获取地图格子的唯一表示
	int tiledGid = collisionLayer->getTileGIDAt(tiledPos);

	//图块ID不为空，表示是障碍物
	if (tiledGid != 0)
	{
		return false;
	}

	this->setPosition(Point(x, y));

	this->setViewPointByHero();

	return true;
}

Point Hero::getTagPosition() {
	return getPosition();
}

Hero* Hero::createFromJsonFile(int modelId) {
	Hero* hero = new Hero();
	if (hero && hero->initFromJsonFileByID(modelId))
		hero->autorelease();
	else
		CC_SAFE_DELETE(hero);

	return hero;
}

bool Hero::initFromJsonFileByID(int modelId) {
	/*
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("sprite.json");
	if (reader.parse(data, root, false) == true) {
		int size = root.size();
		for (int i = 0; i < size; ++i)
			if (modelId == root[i]["Id"].asInt()) {/*Ñ°ÕÒÄ¿±êid*/
			/*	setmodelId(root[i]["Id"].asInt());
				Sprite* sprite = Sprite::create(
					StringUtils::format("hero_%d.png", getmodelId())
				);
				if (sprite && init(sprite)) {
					sethp(root[i]["Hp"].asInt());
					setmp(root[i]["Mp"].asInt());
					setdefense(root[i]["Defense"].asInt());
					setattack(root[i]["Attack"].asInt());
					return true;
				}
			}
	}
	return false;
	*/
	Sprite* sprite = Sprite::create(
		StringUtils::format("hero_%d.png", 1));
	if (sprite && init(sprite))
		return true;

	return false;

}

void Hero::setViewPointByHero() {
	if (_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();

	Size mapTileNum = _safeRoomMap->getMapSize();
	Size tiledSize = _safeRoomMap->getTileSize();

	Size mapSize = Size(mapTileNum.width * tiledSize.width, mapTileNum.height * tiledSize.height);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point spritePos = getPosition();

	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	Point destPos = Point(x, y);
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centerPos - destPos;
	//_safeRoomMap->setPosition(viewPos);
	parent->setPosition(viewPos);
}

void Hero::setSafeRoomTiledMap(TMXTiledMap* map) {
	this->_safeRoomMap = map;
}

void Hero::getHurt(int hurtValue) {
	if (isDead())
		return;

	if (getdefense() >= hurtValue) 
		setDefense(getdefense() - hurtValue);
	else if(getdefense()+gethp()>hurtValue){
		setDefense(0);
		setHp(gethp() - (hurtValue - getdefense()));
	}
	else {
		setDefense(0);
		setHp(0);
		_isDead = true;
		deadResult();
	}
}

void Hero::attack(Entity* entity) {
	
}

void Hero::deadResult() {

}

void Hero::bindHp(LoadingBar* hpBar, Label* hpLabel, Label* hpMaxLabel)
{
	//_hpLoadingBar = hpBar;
	//_hpLabel = hpLabel;
	//_hpMaxLabel = hpMaxLabel;
}

void Hero::bindMp(LoadingBar* mpBar, Label* mpLabel, Label* mpMaxLabel)
{
	//_mpLoadingBar = mpBar;
	//_mpLabel = mpLabel;
	//_mpMaxLabel = mpMaxLabel;
}

void Hero::bindDefense(LoadingBar* defenseBar, Label* defenseLabel, Label* defenseMaxLabel)
{
	//_defenseLoadingBar = defenseBar;
	//_defenseLabel = defenseLabel;
	//_defenseMaxLabel = defenseMaxLabel;
}

void Hero::setMp(int mpValue) {
	//setmp(mpValue);
	//_mpLoadingBar->setPercent(mpValue * 100 / getmpMax());
	//_mpLabel->setString(StringUtils::format("%d", mpValue));
}

void Hero::setMpMax(int mpMaxValue)
{
	//setmpMax(mpMaxValue);
	//_mpLoadingBar->setPercent(getmp() * 100 / mpMaxValue);
	//_mpMaxLabel->setString(StringUtils::format("%d", mpMaxValue));
}

void Hero::setHp(int hpValue) {
	//sethp(hpValue);
	//_hpLoadingBar->setPercent(hpValue * 100 / gethpMax());
	//_hpLabel->setString(StringUtils::format("%d", hpValue));
}

void Hero::setHpMax(int hpMaxValue)
{
	//sethpMax(hpMaxValue);
	//_hpLoadingBar->setPercent(gethp() * 100 / hpMaxValue);
	//_hpMaxLabel->setString(StringUtils::format("%d", hpMaxValue));
}

void Hero::setDefense(int defenseValue) {
	//setdefense(defenseValue);
	//_defenseLoadingBar->setPercent(defenseValue * 100 / getdefenseMax());
	//_defenseLabel->setString(StringUtils::format("%d", defenseValue));
}

void Hero::setDefenseMax(int defenseMaxValue)
{
	//setdefenseMax(defenseMaxValue);
	//_defenseLoadingBar->setPercent(getdefense() * 100 / defenseMaxValue);
	//_defenseMaxLabel->setString(StringUtils::format("%d", defenseMaxValue));
}

GameController* Hero::getMoveController()
{
	return this->_gameController;
}

void Hero::defenseAutoAdd(float dt)
{
	//护盾数+1
	if (this->getdefense() < this->getdefenseMax())
		this->setDefense(this->getdefense() + 1);
	log("Defense is added auto");
}

//设置武器
void Hero::setWeapon(Weapon *weapon)
{
	//加入子类中
	this->addChild(weapon);
	//武器
	this->weapon = weapon;

	CCString weaponType = typeid(*weapon).name();
	//确认武器类型
	if (weaponType._string=="class Gun")
	{
		//类型转换
		Gun* gun = (Gun*)weapon;
		gun->shootController->setMyControlListener(this);

		log("You are taking a GUN!");
	}
	else if (weaponType._string == "class Knife")
	{
		//类型转换
		Knife* knife = (Knife*)weapon;
	}
}

void Hero::setHeroRun(bool rightSide)
{
	if (rightSide)
	{
		this->_sprite->setSpriteFrame(*(rightSpriteVec.begin() + 1));
		
		//组合动画
		Animation* rightAnimation = Animation::createWithSpriteFrames(rightSpriteVec);
		rightAnimation->setLoops(-1);
		rightAnimation->setDelayPerUnit(0.2f);

		Animate* rightAction = Animate::create(rightAnimation);

		this->_sprite->runAction(rightAction);
	}
	else
	{
		this->_sprite->setSpriteFrame(*(leftSpriteVec.begin() + 1));
		//组合动画
		Animation* leftAnimation = Animation::createWithSpriteFrames(leftSpriteVec);
		leftAnimation->setLoops(-1);
		leftAnimation->setDelayPerUnit(0.2f);

		Animate* leftAction = Animate::create(leftAnimation);

		this->_sprite->runAction(leftAction);
	}
}

void Hero::setHeroStill(bool rightSide)
{
	this->_sprite->stopAllActions();
	if (rightSide)
	{
		
		this->_sprite->setSpriteFrame(*(rightSpriteVec.begin() + 1));

	}
	else
	{
		this->_sprite->setSpriteFrame(*(leftSpriteVec.begin() + 1));
		
	}
}

void Hero::update(float dt)
{
	//获取武器样式
	CCString weaponType = typeid(*(this->weapon)).name();
	if (weaponType._string == "class Gun")
	{
		Gun* gun = (Gun*)this->weapon;
		if (GlobalParameter::rightSide)
		{
			if (GlobalParameter::upSide)
			{
				//右上
				gun->weaponSprite->setPosition(20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 1));
			}
			else if (GlobalParameter::downSide)
			{
				//右下
				gun->weaponSprite->setPosition(20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 7));
			}
			else
			{
				//仅朝右
				gun->weaponSprite->setPosition(20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin()));
			}
		}
		else if (GlobalParameter::leftSide)
		{
			if (GlobalParameter::upSide)
			{
				//左上
				gun->weaponSprite->setPosition(-20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 3));
			}
			else if (GlobalParameter::downSide)
			{
				//左下
				gun->weaponSprite->setPosition(-20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 5));
			}
			else
			{
				//仅朝左
				gun->weaponSprite->setPosition(-20, -20);
				gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 4));
			}
		}
		else
		{
			if (GlobalParameter::upSide)
			{
				//仅朝上
				if (GlobalParameter::imageRightSide)
				{
					gun->weaponSprite->setPosition(20, -20);
					gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 2));
				}
				else
				{
					gun->weaponSprite->setPosition(-20, -20);
					gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 2));
				}
			}
			else
			{
				//仅朝下
				if (GlobalParameter::imageRightSide)
				{
					gun->weaponSprite->setPosition(20, -20);
					gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 6));
				}
				else
				{
					gun->weaponSprite->setPosition(-20, -20);
					gun->weaponSprite->setSpriteFrame(*(gun->weaponSpriteVec.begin() + 6));
				}
			}
		}
	}
	else if (weaponType._string == "class Knife")
	{

	}
}