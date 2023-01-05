
#ifndef __Lvl1_H__
#define __Lvl1_H__
#include "cocos2d.h"
#include "player.h"
#include "key.h"
#include "box.h"
#include "door.h"
#include "bridge.h"
#include "ui/UIRichText.h"



class Lvl1 : public cocos2d::Layer
{
public:
    void update(float dt);
    void moveright(float dt);
    void moveleft(float dt);
    void movetop(float dt);
    void pour(float dt);
    void pour2(float dt);
    void pour3(float dt);
    static cocos2d::Scene* createScene();
    float time;
    bool isUpPressed = false;
    bool isRightPressed = false;
    bool isLeftPressed = false;
    bool isSpacePressed = false;
    bool isDoorOpened = false;
    bool isPlayerOnGround = true;
    bool isLightGreen = true;
    cocos2d::Label *timeTxt;
    cocos2d::Label* inst;
    virtual bool init();
    bool onContactBegin(cocos2d::PhysicsContact& contact);

   
    

    
    // implement the "static create()" method manually
    CREATE_FUNC(Lvl1);
    OurPlayer* player;
    OurKey* key;
    OurDoor* door;
    Sprite* ground;
    Sprite* drop;
    Sprite* drop2;
    Sprite* drop3;
    std::vector<bridge*> Bridge;
};

#endif // __Lvl2_H__
