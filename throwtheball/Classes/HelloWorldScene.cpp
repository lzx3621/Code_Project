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
    auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1.0f, 0.0f, 0.5F), 3);
    this->setPhysicsBody(body);
    body->setPositionOffset(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(rootNode,0);
    auto heroCache = CCSpriteFrameCache::getInstance(); 
    heroCache->addSpriteFramesWithFile("Sprite/hero/hero.plist");
    auto sprite = Sprite::createWithSpriteFrame(heroCache->getSpriteFrameByName("Sprite/hero/waiter.png"));
    body = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0F));
    //body->setPositionOffset(sprite->getContentSize()/2);
    sprite->setPhysicsBody(body);

    auto mouseEvent = EventListenerTouchOneByOne::create();
    mouseEvent->onTouchBegan = [=](Touch* touch, Event* event){
        CCLOG("touch x:%f, y:%f", touch->getLocation().x, sprite->getContentSize().height/2);
//         if (event->getCurrentTarget() == sprite)
//         {
//             sprite->setPositionX(touch->getLocation().x);
//         }
        return true;
    };
    mouseEvent->onTouchMoved = [=](Touch* touch, Event* event)
    {
        //锚点在中间位置
        if ((sprite->getContentSize().width)/2 >= abs(sprite->getPositionX() - touch->getLocation().x))
        {
            sprite->setPositionX(touch->getLocation().x);
        }
        //sprite->setPosition(0, 0);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseEvent, sprite);

    /*rootNode->*/addChild(sprite);

    sprite->setAnchorPoint(Vec2(0.5,0.5));

    sprite->setPosition(sprite->getContentSize());
//     auto fileUtil = FileUtils::getInstance();
//     std::string fliename(fileUtil->getWritablePath()+"appConfig.plist");
//     fliename = fileUtil->fullPathFromRelativeFile("res",fliename);
//     ValueMap appConfig;
//     if (fileUtil->isFileExist(fliename))
//     {
//          appConfig= fileUtil->getValueMapFromFile(fliename);
//     }
//     else
//     {
//         Value iValue(3621);
//         appConfig.insert(ValueMap::value_type("test",iValue));
//         fileUtil->writeToFile(appConfig, fliename);
//     }

    return true;
}
