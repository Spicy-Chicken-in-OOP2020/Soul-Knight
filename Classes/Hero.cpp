#include "Hero.h"

Hero::Hero() :_weapon(1) {}//Ä¬ÈÏÐ¡ÊÖÇ¹

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

	bindSprite(sprite);

	return true;
}

void Hero::setController(GameController* gameController, GameController* shotController) {
	_gameController = gameController;
	_shotController = shotController;
	log("ShootController is added!\n");
	_gameController->setMyControlListener(this);
	_shotController->setMyControlListener(this);
	this->addChild(_shotController);
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
	_hpLoadingBar = hpBar;
	_hpLabel = hpLabel;
	_hpMaxLabel = hpMaxLabel;
}

void Hero::bindMp(LoadingBar* mpBar, Label* mpLabel, Label* mpMaxLabel)
{
	_mpLoadingBar = mpBar;
	_mpLabel = mpLabel;
	_mpMaxLabel = mpMaxLabel;
}

void Hero::bindDefense(LoadingBar* defenseBar, Label* defenseLabel, Label* defenseMaxLabel)
{
	_defenseLoadingBar = defenseBar;
	_defenseLabel = defenseLabel;
	_defenseMaxLabel = defenseMaxLabel;
}

void Hero::setMp(int mpValue) {
	setmp(mpValue);
	_mpLoadingBar->setPercent(mpValue * 100 / getmpMax());
	_mpLabel->setString(CCString::createWithFormat("%d", getmp())->getCString());
}

void Hero::setHp(int hpValue) {
	setmp(hpValue);
	_mpLoadingBar->setPercent(hpValue * 100 / gethpMax());
	_mpLabel->setString(CCString::createWithFormat("%d", gethp())->getCString());
}

void Hero::setDefense(int defenseValue) {
	setmp(defenseValue);
	_mpLoadingBar->setPercent(defenseValue * 100 / getdefenseMax());
	_mpLabel->setString(CCString::createWithFormat("%d", getdefense())->getCString());
}

GameController* Hero::getMoveController()
{
	return this->_gameController;
}