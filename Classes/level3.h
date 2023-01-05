
#ifndef __Lvl3_H__
#define __Lvl3_H__
#include "cocos2d.h"
#include "player.h"
#include "key.h"
#include "box.h"
#include "door.h"
#include "bridge.h"
#include "ui/UIRichText.h"



class Lvl3 : public cocos2d::Layer
{
public:
    void update(float dt);
    void moveright(float dt);
    void moveleft(float dt);
    void movetop(float dt);
    void movebot(float dt);
    static cocos2d::Scene* createScene();
    float time;
    bool isUpPressed = false;
    bool isRightPressed = false;
    bool isLeftPressed = false;
    bool isSpacePressed = false;
    bool isDoorOpened = false;
    bool isPlayerOnGround = true;
    float angle = 0.0;
    cocos2d::Label *timeTxt;
    cocos2d::Label* inst;
    virtual bool init();
    bool onContactBegin(cocos2d::PhysicsContact& contact);

   
    

    
    // implement the "static create()" method manually
    CREATE_FUNC(Lvl3);
    OurPlayer* player;
    OurKey* key;
    OurDoor* door;
    Label* timeTxt0;
    Sprite* ground;
    Sprite* plat1;
    Sprite* plat2;
    Sprite* plat3;
    Sprite* plat4;
    Sprite* ball;
    Sprite* button;
    Sprite* rotateLeft;
    Sprite* rotateRight;
};

#endif // __Lvl2_H__
