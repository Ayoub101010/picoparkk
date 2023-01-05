#include "level1.h"
#include "level2.h"
#include "ui/UITextField.h"

USING_NS_CC;

Scene* Lvl1::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,-400));
    scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    auto layer = Lvl1::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool Lvl1::init()
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
    
    
    ground = Sprite::create("ground.png");
    ground->setScale(2.05);
    auto Frame4body = PhysicsBody::createBox(Size(ground->getContentSize().width, ground->getContentSize().height), PhysicsMaterial(0, 0, 0));
    Frame4body->setCollisionBitmask(2);
    Frame4body->setContactTestBitmask(true);
    ground->setPosition(Point(origin.x + 80, origin.y + 100));
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
    gound2->setPosition(Point(origin.x + 975, origin.y + 100));
    if (gound2body != nullptr)
    {
        gound2body->setDynamic(false);
        gound2->setPhysicsBody(gound2body);
    }
    this->addChild(gound2);

    auto lava = Sprite::create("lavaPool.png");
    lava->setPosition(Point(origin.x + 525, origin.y +350));
    lava->setScale(0.6);
    this->addChild(lava);

    player = new OurPlayer(this);
    player->setposition(origin.x + 200, origin.y + 200);
    key = new OurKey(this);
    key->setposition(visibleSize.width - 200, origin.y +200);
    door = new OurDoor(this);
    door->setposition(visibleSize.width - 100, origin.y + 170);
    door->setposition2(visibleSize.width - 100, origin.y + 170);

    this->scheduleUpdate();
;
    
       
        for (int i = 1; i <= 9; i++) {
          
                auto _sprite = bridge::bridgeinit();
                auto _spritebody = PhysicsBody::createBox(Size(_sprite->getContentSize().width, _sprite->getContentSize().height), PhysicsMaterial(0, 0, 0));
                _spritebody->setCollisionBitmask(2);
                _spritebody->setContactTestBitmask(true);
                _sprite->setPosition(Point(origin.x + 1025, origin.y + 100));
                if (_spritebody != nullptr)
                {
                    _spritebody->setDynamic(false);
                    _sprite->setPhysicsBody(_spritebody);
                }
                _sprite->setPosition(Vec2(origin.x +352.5+ i * 35, origin.y + 85));

                this->addChild(_sprite, 1);
                Bridge.push_back(_sprite);
        }
   
  
   
        this->schedule(SEL_SCHEDULE(&Lvl1::pour), 3.5);
        this->schedule(SEL_SCHEDULE(&Lvl1::pour2), 2.5);
        this->schedule(SEL_SCHEDULE(&Lvl1::pour3), 1.5);
    

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
     
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
            case EventKeyboard::KeyCode::KEY_A:
              
                isLeftPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl1::moveleft), 0.01);
                
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl1::moveright), 0.01);
                 
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (isSpacePressed == false)
                {
                    this->schedule(SEL_SCHEDULE(&Lvl1::movetop), 0.01);
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
                    this->unschedule(SEL_SCHEDULE(&Lvl1::moveleft));
                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isRightPressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl1::moveright));
                   
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:

                    this->unschedule(SEL_SCHEDULE(&Lvl1::movetop));
                        
                  
                 
                   
                break;
          
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = false;

                break;
         
            }
    };
    

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    auto contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactBegin = CC_CALLBACK_1(Lvl1::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void Lvl1::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void Lvl1::moveleft(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x - 80 * dt, playerPos.y);
}

void Lvl1::movetop(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x, playerPos.y + 160 * dt);
}
void Lvl1::pour(float dt)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    drop = Sprite::create("lavaDrop.png");
    drop->setScale(1.2);
    drop->setPosition(Point(origin.x + 525, origin.y + 300));
    auto dropBody = PhysicsBody::createBox(Size(drop->getContentSize().width , drop->getContentSize().height ), PhysicsMaterial(0, 0, 0));
    dropBody->setCollisionBitmask(10);
    dropBody->setContactTestBitmask(true);
    dropBody->setDynamic(false);
    drop->setPhysicsBody(dropBody);
    auto fire = MoveTo::create(2, Point(origin.x + 525, origin.y - 100));
    drop->runAction(fire);
    this->addChild(drop);
}
void Lvl1::pour2(float dt)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    drop2 = Sprite::create("lavaDrop.png");
    drop2->setScale(1.2);
    drop2->setPosition(Point(origin.x + 630, origin.y + 300));
    auto drop2Body = PhysicsBody::createBox(Size(drop2->getContentSize().width , drop2->getContentSize().height ), PhysicsMaterial(0, 0, 0));
    drop2Body->setCollisionBitmask(10);
    drop2Body->setContactTestBitmask(true);
    drop2Body->setDynamic(false);
    drop2->setPhysicsBody(drop2Body);
    auto fire = MoveTo::create(2, Point(origin.x + 630, origin.y - 100));
    drop2->runAction(fire);
    this->addChild(drop2);
}
void Lvl1::pour3(float dt)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    drop3 = Sprite::create("lavaDrop.png");
    drop3->setScale(1.2);
    drop3->setPosition(Point(origin.x + 425, origin.y + 300));
    auto drop3Body = PhysicsBody::createBox(Size(drop3->getContentSize().width , drop3->getContentSize().height ), PhysicsMaterial(0, 0, 0));
    drop3Body->setCollisionBitmask(10);
    drop3Body->setContactTestBitmask(true);
    drop3Body->setDynamic(false);
    drop3->setPhysicsBody(drop3Body);
    auto fire = MoveTo::create(2, Point(origin.x + 425, origin.y-100));
    drop3->runAction(fire);
    this->addChild(drop3);
}

bool Lvl1::onContactBegin(cocos2d::PhysicsContact& contact)
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
        auto scene = Lvl1::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
    }
    else if ((10 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) || (1 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask())) {

        isDoorOpened = false;
        auto scene = Lvl1::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
    }


    return true;
}
 

void Lvl1::update(float dt) {
        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect5 = ground->getBoundingBox();
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
            auto scene = Lvl2::createScene();
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
   


}