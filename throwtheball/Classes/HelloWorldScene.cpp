#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vect(0.0f, -98.0f));
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");


    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    this->setPhysicsBody(body);
    body->setPositionOffset(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(rootNode,0);
    auto heroCache = CCSpriteFrameCache::getInstance(); 
    heroCache->addSpriteFramesWithFile("Sprite/hero/hero.plist");
    auto sprite = Sprite::createWithSpriteFrame(heroCache->getSpriteFrameByName("Sprite/hero/waiter.png"));
    sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getContentSize()));
    
    auto mouseEvent = EventListenerTouchOneByOne::create();
    mouseEvent->onTouchBegan = [=](Touch* touch, Event* event){
        sprite->setPosition(touch->getLocation());
        return true;
    };
    mouseEvent->onTouchMoved = [=](Touch* touch, Event* event)
    {
        auto sprite1 = static_cast<Sprite *>(event->getCurrentTarget());
        sprite->setPosition(touch->getLocation());
        //sprite->setPosition(0, 0);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEvent, sprite);
    /*rootNode->*/addChild(sprite);
    
    return true;
}
