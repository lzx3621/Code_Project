#include "CCGameSceneNormal.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCNormalRule.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CCGameSceneNormal::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = CCGameSceneNormal::create();


    // add layer as a child to scene
    scene->addChild(layer, 0, "CCGameSceneNormal");
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CCGameSceneNormal::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("GameSceneNormal.csb");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1000.0f, 0.0f, 0.0F), 3.0f);
    body->setPositionOffset(Point(visibleSize.width/2, visibleSize.height/2));
	this->setPhysicsBody(body);
    addChild(rootNode);
    CCNormalRule::create(this);
    return true;
}

void CCGameSceneNormal::startGame()
{
    getChildByName<CCRule*>("Rule")->onStart();
}
