#include "box.h"

USING_NS_CC;

OurBox::OurBox(cocos2d::Layer* layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Pico = Sprite::create("box.png");
	Pico->setScale(1.2);
	Pico->setPosition(Point(origin.x+300, origin.y+68));
	auto  Playerbody = PhysicsBody::createBox(Pico->getContentSize(), PhysicsMaterial(0, 0, 0));
	Playerbody->setCollisionBitmask(4);
	Playerbody->setContactTestBitmask(true);
	Playerbody->setDynamic(false);
	Pico->setPhysicsBody(Playerbody);
	

	
	layer->addChild(Pico, 1);
};

cocos2d::Vec2 OurBox::getposition() {
	return Pico->getPosition();
}

void  OurBox::setDynamic(bool dynamic) {
	Pico->getPhysicsBody()->setDynamic(dynamic);
}
void  OurBox::setposition(float x, float y) {
	Pico->setPosition(Point(x, y));
}
void OurBox::setScale(float x)
{
	Pico->setScale(x);
}
void OurBox::fall() {
	Pico->getPhysicsBody()->removeFromWorld();
}
void OurBox::removeFromParent() {
	Pico->setVisible(false);
}
cocos2d::Rect OurBox::getrect() {
	return Pico->getBoundingBox();
}
