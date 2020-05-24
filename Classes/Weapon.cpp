#include "Weapon.h"

Weapon::Weapon(int attackData,String name) 
{
	//init
	this->init();

	this->setAttack(attackData);

	this->bindSprite();

	this->weaponName = name;
}

bool Weapon::init()
{
	if (!Node::init())
		return false;

	return true;
}

void Weapon::bindSprite()
{
	this->weaponSprite = Sprite::create("KnightImage.png");
	this->addChild(weaponSprite);
}

Sprite* Weapon::getWeapnSprite()
{
	return this->weaponSprite;
}