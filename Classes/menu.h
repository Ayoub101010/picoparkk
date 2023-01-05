#ifndef _MENU_H_
#define _MENU_H_

#include "cocos2d.h"
#include "player.h"


class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
   // void update(float dt)

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    OurPlayer* player;


    void GoToLVL1(cocos2d::Ref* pSender);
   
};

#endif // _MAIN_MENU_SCENE_H_