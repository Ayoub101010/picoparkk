#include "key.h"

USING_NS_CC;

OurKey::OurKey(cocos2d::Layer* layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	key = Sprite::create("key.png");
	key->setScale(0.1);
	key->setPosition(Point(origin.x +550, origin.y+150));
	layer->addChild(key, 1);
};

cocos2d::Vec2 OurKey::getposition() {
	return key->getPosition();
}

void  OurKey::setposition(float x, float y) {
	key->setPosition(Point(x, y));
}
void OurKey::removeFromParent() {
	key->setVisible(false);
}

cocos2d::Rect OurKey::getrect() {
	return key->getBoundingBox();
}