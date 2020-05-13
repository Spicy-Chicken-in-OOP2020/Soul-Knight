#include "Hero.h"


Hero::Hero() :_weapon(1) {}//默认小手枪

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

void Hero::setController(GameController * gamecontroller) {
	_gameController = gamecontroller;
	_gameController->setMyControlListener(this);
}

void Hero::setTagPosition(int x, int y) {
	setPosition(Point(x, y));
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
			if (modelId == root[i]["Id"].asInt()) {/*寻找目标id*/
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

void Hero::getHurt(int hurtValue) {
	if (isDead())
		return;

	int hp = gethp() - hurtValue;
	if (hp <= 0) {
		sethp(0);
		_isDead = true;
		deadResult();
	}
	else
		sethp(hp);

}

void Hero::attack(Entity * entity) {
	entity->getHurt(getattack());
}

void Hero::deadResult() {

}

void Hero::addMp() {

}

void Hero::addHp() {

}