#include "CCGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCNormalRule.h"
#include "ui/UITextBMFont.h"

USING_NS_CC;

using namespace cocostudio::timeline;

CCGameScene * CCGameScene::create(Scene* scene)
{
    auto *pRet = new(std::nothrow) CCGameScene(); 
    if (pRet && pRet->init(scene)) 
    { 
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

Scene* CCGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    if (nullptr != scene)
    {
        auto layer = CCGameScene::create(scene);
        if (nullptr != layer)
        {
            scene->addChild(layer);
            scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
            return scene;
        }
        
    }

    return nullptr;
}

// on "init" you need to initialize your instance
bool CCGameScene::init(Scene* scene)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    setName("CCGameScene");
    auto rootNode = CSLoader::createNode("Scene/Game/GameLayer.csb");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.0F), 3.0f);
    body->setPositionOffset(Point(visibleSize.width/2, visibleSize.height/2));
    body->setCategoryBitmask(0x1);
    body->setContactTestBitmask(0x2);
    body->setCollisionBitmask(0x6);
    
    Node::addChild(rootNode);
    setPhysicsBody(body);
    Node::addChild(CCNormalRule::create(this));
    return true;
}

void CCGameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gameStart();
}

void CCGameScene::onExitTransitionDidStart()
{
    Layer::onEnterTransitionDidFinish();
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gameOver();
}

void CCGameScene::updateheroScoreAndLive(int Hero, int score)
{
    char temp[64] = {0};
    sprintf(temp, "%d", score);
    (getChildByName("GameLayer")->getChildByName("tilte")->getChildByName<ui::TextBMFont*>("Label_Score"))->setString(temp);
    sprintf(temp, "X %d", Hero);
    (getChildByName("GameLayer")->getChildByName("tilte")->getChildByName<ui::TextBMFont*>("Label_live"))->setString(temp);
}

void CCGameScene::addChild(Node * child)
{
    getChildByName("GameLayer")->getChildByName("background")->addChild(child);
}

void CCGameScene::addRole(cocos2d::Node* Role)
{
    getChildByName("GameLayer")->getChildByName("background")->addChild(Role);
}

cocos2d::Scene* CCGameScene::getGameScene()
{
    return getScene();
}

