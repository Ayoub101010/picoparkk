#include "menu.h"
#include "level1.h"



USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    LayerColor* _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(_bgColor, -10);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

   
    auto playItem = MenuItemFont::create("START", CC_CALLBACK_1(MainMenu::GoToLVL1, this));
    playItem->setColor(Color3B::BLACK);
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(visibleSize.width/2, visibleSize.height/2 );
    this->addChild(menu);

    return true;
}



void MainMenu::GoToLVL1(cocos2d::Ref* pSender)
{
    
    auto scene = Lvl1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}