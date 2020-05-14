#include "Entity.h"
Entity::Entity()
	:_sprite(nullptr), _isDead(false), _modelId(0), _hp(0), _defense(0), _mp(0), _attack(0) {}

Entity::~Entity() = default;


void Entity::bindSprite(Sprite * sprite) {
	if (_sprite)
		_sprite->removeFromParentAndCleanup(true);

	_sprite = sprite;
	this->addChild(_sprite);

	Size size = _sprite->getContentSize();
	this->setContentSize(size);

}

Sprite* Entity::getSprite() {
	return _sprite;
}

bool Entity::isDead() {
	return _isDead;
}