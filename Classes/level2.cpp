#include "level2.h"
#include "ui/UITextField.h"
#include "level3.h"

USING_NS_CC;
Scene* Lvl2::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    auto layer = Lvl2::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool Lvl2::init()
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
    
    this->setScale(1.3);
    ground = Sprite::create("ground.png");
    ground->setScale(2.05);
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
    gound2->setScale(2.05);
    auto gound2body = PhysicsBody::createBox(Size(gound2->getContentSize().width, gound2->getContentSize().height), PhysicsMaterial(0, 0, 0));
    gound2body->setCollisionBitmask(2);
    gound2body->setContactTestBitmask(true);
    gound2->setPosition(Point(origin.x + 900, origin.y + 15));
    if (gound2body != nullptr)
    {
        gound2body->setDynamic(false);
        gound2->setPhysicsBody(gound2body);
    }
    this->addChild(gound2);



    player = new OurPlayer(this);
    player->setposition(origin.x + 200, origin.y + 90);
    key = new OurKey(this);
    key->setposition(visibleSize.width - 100, origin.y +210);
    door = new OurDoor(this);
    door->setposition(origin.x +100, origin.y + 85);
    door->setposition2(origin.x + 100, origin.y + 85);
    box = new OurBox(this);
    auto camera = Camera::create();
    camera->setPositionZ(5);
    camera->clearBackground();
    this->addChild(camera);
    this->scheduleUpdate();

   
    plusButton = Sprite::create("button.png");
    plusButton->setScale(0.10);
    plusButton->setPosition(Point(visibleSize.width - 100, origin.y + 55));
    auto timeTxt1 = Label::createWithTTF("+", "fonts/arial.ttf", 25);
    timeTxt1->setTextColor(Color4B::BLACK);
    timeTxt1->setPosition(Vec2(visibleSize.width - 100, origin.y + 65));
    this->addChild(plusButton);
    this->addChild(timeTxt1);
   
    

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
     
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
            case EventKeyboard::KeyCode::KEY_A:
              
                isLeftPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl2::moveleft), 0.01);
                
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl2::moveright), 0.01);
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (isSpacePressed == false)
                {
                    this->schedule(SEL_SCHEDULE(&Lvl2::movetop), 0.01);
                    isSpacePressed = true;
                    isPlayerOnGround = false;
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
                    this->unschedule(SEL_SCHEDULE(&Lvl2::moveleft));
                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl2::moveright));
                  
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:

                    this->unschedule(SEL_SCHEDULE(&Lvl2::movetop));
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
             
                    this->unschedule(SEL_SCHEDULE(&Lvl2::movebot));
                   
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = false;

                break;
         
            }
    };
    

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //we create a contact listener to detect the collision of the ball with te walls and the obstacles
    auto contactListener = EventListenerPhysicsContact::create();
    //make a call back to the function everytime a contact happen
    contactListener->onContactBegin = CC_CALLBACK_1(Lvl2::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void Lvl2::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void Lvl2::moveleft(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x - 80 * dt, ballpos.y);
}
void Lvl2::movebot(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y -80 * dt);
}
void Lvl2::movetop(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y + 160 * dt);
}

bool Lvl2::onContactBegin(cocos2d::PhysicsContact& contact)
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
        auto scene = Lvl2::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
    }
    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        isSpacePressed = false;
        if (isRightPressed) {
            box->setposition(box->getposition().x + 4, box->getposition().y);

        }
        else if (isLeftPressed)
        {
            box->setposition(box->getposition().x - 4, box->getposition().y);
        }

    }

    return true;
}
 

void Lvl2::update(float dt) {
   
  


        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect5 = ground->getBoundingBox();
        Rect rect7 = plusButton->getBoundingBox();
        Rect rect8 = box->getrect();

        auto v = Director::getInstance()->getWinSize();
        Layer::setAnchorPoint(Vec2(player->getposition().x / v.width, player->getposition().y /v.height));
         
        if (rect1.intersectsRect(rect2))
        {
            key->setposition(player->getposition().x-10, player->getposition().y);
            
            
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
            auto scene = Lvl3::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }
        if (isLeftPressed)
        {
            player->turnLeft(180);
        }
        else if (isRightPressed)
        {
            player->turnRight();

        }
        if (rect1.intersectsRect(rect7))
        {
            if (size<1)
            {
                size += dt;
                player->setscale(size);
            }
            
        }
        


        //condition to moove to next level 

}