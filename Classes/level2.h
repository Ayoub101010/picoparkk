
#ifndef __Lvl2_H__
#define __Lvl2_H__
#include "cocos2d.h"
#include "player.h"
#include "key.h"
#include "box.h"
#include "door.h"
#include "bridge.h"
#include "ui/UIRichText.h"



class Lvl2 : public cocos2d::Layer
{
public:
    void update(float dt);
    void moveright(float dt);
    void moveleft(float dt);
    void movetop(float dt);
    void movebot(float dt);
    static cocos2d::Scene* createScene();
    float size=0.4;
    float boxSize = 1.2;
    bool isUpPressed = false;
    bool isRightPressed = false;
    bool isLeftPressed = false;
    bool isSpacePressed = false;
    bool isDoorOpened = false;
    bool isPlayerOnGround = true;

    cocos2d::Label *timeTxt;
    cocos2d::Label* inst;
    virtual bool init();
    bool onContactBegin(cocos2d::PhysicsContact& contact);

   
    

    
    // implement the "static create()" method manually
    CREATE_FUNC(Lvl2);
    OurPlayer* player;
    OurKey* key;
    OurDoor* door;
    Sprite* ground;
    Sprite* wall;
    Sprite* minusButton;
    Sprite* plusButton;
    OurBox* box;
    Action* walking;
    Action* jumping;
    Action* landing;
};

#endif // __Lvl2_H__
