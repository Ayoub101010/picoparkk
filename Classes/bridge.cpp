#include "bridge.h"

USING_NS_CC;

bridge::bridge(void) {
	this->isClaimed = false;
};

bridge* bridge::bridgeinit() {
	auto sprite = new bridge();
	sprite->initWithFile("box.png");
	sprite->setScale(1.2);
	return sprite;
}