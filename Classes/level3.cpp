#include "level3.h"
#include "menu.h"
#include "ui/UITextField.h"

USING_NS_CC;

Scene* Lvl3::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    //scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    auto layer = Lvl3::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool Lvl3::init()
{
    if (!Layer::init())
    {
        return false;
    }

    //------------------------------------------------------------create backgroud color-------------------------------------------------

    LayerColor* _bgColor = LayerColor::create(Color4B::WHITE);
    this->addChild(_bgColor, -10);

    //---------------------------------------------create variables for positioning our instance-------------------------------------------------------

    auto visibleSize = Director::getInstance()->getWinSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //-------------------------------------------------create an edge box for our game------------------------------------------------------

    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgebody->setCollisionBitmask(3);
    edgebody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point((visibleSize.width / 2) , (visibleSize.height / 2)));
    edgeNode->setPhysicsBody(edgebody);
    this->addChild(edgeNode);
    
    this->scheduleUpdate();
    ground = Sprite::create("ground.png");
    ground->setScale(2.2);
    ground->setRotation3D(Vec3(0, 0, 0));
    auto Frame4body = PhysicsBody::createBox(Size(ground->getContentSize().width, ground->getContentSize().height), PhysicsMaterial(0, 0, 0));
    Frame4body->setCollisionBitmask(2);
    Frame4body->setContactTestBitmask(true);
    ground->setPosition(Point(origin.x + 200, origin.y + 15));
    if (Frame4body != nullptr)
    {
        Frame4body->setDynamic(false);
        ground->setPhysicsBody(Frame4body);
    }
    this->addChild(ground);

    auto gound2 = Sprite::create("ground.png");
    gound2->setScale(2.2);
    auto gound2body = PhysicsBody::createBox(Size(gound2->getContentSize().width, gound2->getContentSize().height), PhysicsMaterial(0, 0, 0));
    gound2body->setCollisionBitmask(2);
    gound2body->setContactTestBitmask(true);
    gound2->setPosition(Point(origin.x + 1000, origin.y + 15));
    if (gound2body != nullptr)
    {
        gound2body->setDynamic(false);
        gound2->setPhysicsBody(gound2body);
    }
    this->addChild(gound2);
    plat1 = Sprite::create("ground.png");
    plat1->setScale(0.8);
    plat1->setRotation3D(Vec3(0, 0, 0));
    auto plat1body = PhysicsBody::createBox(Size(plat1->getContentSize().width, plat1->getContentSize().height), PhysicsMaterial(0, 0, 0));
    plat1body->setCollisionBitmask(2);
    plat1body->setContactTestBitmask(true);
    plat1->setPosition(Point(origin.x + 450, origin.y + 400));
    if (plat1body != nullptr)
    {
        plat1body->setDynamic(false);
        plat1->setPhysicsBody(plat1body);
    }
    this->addChild(plat1);
    plat2 = Sprite::create("ground.png");
    plat2->setScale(0.8);
    plat2->setRotation3D(Vec3(0, 0, 0));
    auto plat2body = PhysicsBody::createBox(Size(plat2->getContentSize().width, plat2->getContentSize().height), PhysicsMaterial(0, 0, 0));
    plat2body->setCollisionBitmask(2);
    plat2body->setContactTestBitmask(true);
    plat2->setPosition(Point(origin.x + 550, origin.y + 300));
    if (plat2body != nullptr)
    {
        plat2body->setDynamic(false);
        plat2->setPhysicsBody(plat2body);
    }
    this->addChild(plat2);
    plat3 = Sprite::create("ground.png");
    plat3->setScale(0.8);
    plat3->setRotation3D(Vec3(0, 0, 0));
    auto plat3body = PhysicsBody::createBox(Size(plat3->getContentSize().width, plat3->getContentSize().height), PhysicsMaterial(0, 0, 0));
    plat3body->setCollisionBitmask(2);
    plat3body->setContactTestBitmask(true);
    plat3->setPosition(Point(origin.x + 450, origin.y + 200));
    if (plat3body != nullptr)
    {
        plat3body->setDynamic(false);
        plat3->setPhysicsBody(plat3body);
    }
    this->addChild(plat3);

    plat4= Sprite::create("ground.png");
    plat4->setScale(0.8);
    auto plat4body = PhysicsBody::createBox(Size(plat4->getContentSize().width, plat4->getContentSize().height), PhysicsMaterial(0, 0, 0));
    plat4body->setCollisionBitmask(2);
    plat4body->setContactTestBitmask(true);
    plat4->setPosition(Point(origin.x + 350, origin.y + 40));
    if (plat4body != nullptr)
    {
        plat4body->setDynamic(false);
        plat4->setPhysicsBody(plat4body);
    }
    this->addChild(plat4);


    player = new OurPlayer(this);
    player->setposition(origin.x + 200, origin.y + 90);
    key = new OurKey(this);
    key->setposition(visibleSize.width - 100, origin.y +80);
    door = new OurDoor(this);
    door->setposition(origin.x +100, origin.y + 85);
    door->setposition2(origin.x + 100, origin.y + 85);
  

    ball = Sprite::create("ball.png");
    auto ballbody = PhysicsBody::createCircle(ball->getContentSize().width/2, PhysicsMaterial(0, 0, 0));
    ballbody->setCollisionBitmask(15);
    ballbody->setContactTestBitmask(true);
    
    ball->setPosition(Point(origin.x + 400, origin.y + 450));
    if (ballbody != nullptr)
    {
        ballbody->setDynamic(true);
        ball->setPhysicsBody(ballbody);
    }
    this->addChild(ball);

    rotateRight = Sprite::create("button.png");
    rotateRight->setScale(0.15);
    rotateRight->setPosition(Point(origin.x + 250, origin.y + 60));
    auto timeTxt = Label::createWithTTF("+", "fonts/arial.ttf", 25);
    timeTxt->setTextColor(Color4B::BLACK);
    timeTxt->setPosition(Vec2(origin.x + 250, origin.y + 75));
    this->addChild(rotateRight);
    this->addChild(timeTxt);


    rotateLeft = Sprite::create("button.png");
    rotateLeft->setScale(0.15);
    rotateLeft->setPosition(Point(origin.x + 300, origin.y + 60));
    auto timeTxt1 = Label::createWithTTF("-", "fonts/arial.ttf", 25);
    timeTxt1->setTextColor(Color4B::BLACK);
    timeTxt1->setPosition(Vec2(origin.x + 300, origin.y + 75));
    this->addChild(rotateLeft);
    this->addChild(timeTxt1);
    
    button = Sprite::create("button.png");
    button->setScale(0.15);
    button->setPosition(Point(visibleSize.width - 330, origin.y + 5));
    auto buttonbody = PhysicsBody::createBox(Size(button->getContentSize().width, button->getContentSize().height), PhysicsMaterial(0, 0, 0));
    buttonbody->setCollisionBitmask(16);
    buttonbody->setContactTestBitmask(true);
    if (buttonbody != nullptr)
    {
        buttonbody->setDynamic(true);
        button->setPhysicsBody(buttonbody);
    }
    this->addChild(button);


   
  
   
   
    

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
     
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
            case EventKeyboard::KeyCode::KEY_A:
              
                isLeftPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl3::moveleft), 0.01);
                
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl3::moveright), 0.01);
                 
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (isSpacePressed == false )
                {
                    this->schedule(SEL_SCHEDULE(&Lvl3::movetop), 0.01);
                 
                   
                   
                    isPlayerOnGround = false;
                    
                    {
                        isSpacePressed = true;
                    }
                }
                
                   
                    
            
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = true;

                break;
                  
            } 

      
           

    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
   
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
              
                isLeftPressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl3::moveleft));

                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl3::moveright));

                  
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                    this->unschedule(SEL_SCHEDULE(&Lvl3::movetop));
                   
                  
                 
                   
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
             
                    this->unschedule(SEL_SCHEDULE(&Lvl3::movebot));
                   
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = false;

                break;
         
            }
    };
    
    timeTxt0 = Label::createWithTTF("tab3k", "fonts/Marker Felt.ttf", 25);
    timeTxt0->setTextColor(Color4B::BLACK);
   
    this->addChild(timeTxt0);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //we create a contact listener to detect the collision of the ball with te walls and the obstacles
    auto contactListener = EventListenerPhysicsContact::create();
    //make a call back to the function everytime a contact happen
    contactListener->onContactBegin = CC_CALLBACK_1(Lvl3::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void Lvl3::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void Lvl3::moveleft(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x - 80 * dt, ballpos.y);
}
void Lvl3::movebot(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y -80 * dt);
}
void Lvl3::movetop(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y + 160* dt);
}

bool Lvl3::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    auto p = contact.getContactData()->points;

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        isSpacePressed = false;
    }
    else if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        isDoorOpened = false;
        auto scene = Lvl3::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
    }
    else if((16 == a->getCollisionBitmask() && 15 == b->getCollisionBitmask()) || (15 == a->getCollisionBitmask() && 16 == b->getCollisionBitmask()))
    {
        auto move = MoveTo::create(2, Vec2(600, plat4->getPosition().y));
        plat4->runAction(move);
    }
    return true;
}
 

void Lvl3::update(float dt) {
        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect5 = ground->getBoundingBox();
        Rect rect6 = rotateLeft->getBoundingBox();
        Rect rect7 = rotateRight->getBoundingBox();
        auto v = Director::getInstance()->getWinSize();
        Layer::setAnchorPoint(Vec2(player->getposition().x / v.width, player->getposition().y /v.height));
         
        if (rect1.intersectsRect(rect2))
        {
            key->setposition(player->getposition().x-10, player->getposition().y + 10);
            
            
        }
        if (rect2.intersectsRect(rect3) && isUpPressed == true && isDoorOpened == false) {
            key->removeFromParent();
            door->OpenDoor();
            //isDpressed = true;
            isDoorOpened = true;
            isUpPressed = false;
            
        }
        if (rect1.intersectsRect(rect3) && isDoorOpened == true && isUpPressed==true) {
            isUpPressed = false;
            auto scene = MainMenu::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.8, scene));
        }
        if (rect1.intersectsRect(rect6) ) {
            angle -= 2*dt;
            plat1->setRotation3D(Vec3(0, 0, angle));
            plat2->setRotation3D(Vec3(0, 0, angle) );
            plat3->setRotation3D(Vec3(0, 0, angle));
        }
        if (rect1.intersectsRect(rect7)) {
            angle += 2*dt;
            plat1->setRotation3D(Vec3(0, 0, angle));
            plat2->setRotation3D(Vec3(0, 0, angle));
            plat3->setRotation3D(Vec3(0, 0, angle));
        }
        if (isLeftPressed)
        {
            player->turnLeft(180);
        }
        else if (isRightPressed)
        {
            player->turnRight();

        }

        //condition to moove to next level 

}