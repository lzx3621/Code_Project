#include "CCGameSceneNormal.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameSceneNormal::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = GameSceneNormal::create();


    // add layer as a child to scene
    scene->addChild(layer);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSceneNormal::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("GameSceneNormal.csb");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	this->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->setPhysicsBody(body);
    addChild(rootNode);

    return true;
}
