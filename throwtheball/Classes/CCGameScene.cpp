#include "CCGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCNormalRule.h"
#include "ui/UITextBMFont.h"

USING_NS_CC;

using namespace cocostudio::timeline;

CCGameScene::~CCGameScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_pauseLayer);
}
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
    
    
    if (!initRoot() ||
        !initPuase() ||
        !Layer::init() )
    {
        return false;
    }
    setName("CCGameScene");

    Size visibleSize = _rootNode->getContentSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.0F), 3.0f);
    body->setPositionOffset(Point(visibleSize.width/2, visibleSize.height/2));
    body->setCategoryBitmask(0x1);
    body->setContactTestBitmask(0x2);
    body->setCollisionBitmask(0x6);
    setPhysicsBody(body);
    scene->addChild(this);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    addChild(_rootNode);
    addChild(CCNormalRule::create(dynamic_cast<CCGameUIAdapter *>(this)));
    return true;
}

bool CCGameScene::initPuase()
{
    _pauseLayer = CSLoader::createNode("Pop/Pause.csb");
    if (nullptr == _pauseLayer)
    {
        return false;
    }
    _pauseLayer->retain();
    auto button= _pauseLayer->getChildByName<ui::Button*>("back");
    button->addClickEventListener(CC_CALLBACK_1(CCGameScene::resume, this));
    button= _pauseLayer->getChildByName<ui::Button*>("level");
    button->addClickEventListener(CC_CALLBACK_1(CCGameScene::back, this));
    button= _pauseLayer->getChildByName<ui::Button*>("replay");
    button->addClickEventListener(CC_CALLBACK_1(CCGameScene::restart, this));
    return true;
}

bool CCGameScene::initRoot()
{
    _rootNode = CSLoader::createNode("Scene/Game/GameLayer.csb");
    if (nullptr == _rootNode)
    {
        return false;
    }
    _rootNode->retain();
    
    auto tools = _rootNode->getChildByName("tilte")->getChildByName<ui::Button*>("tools");
    tools->addClickEventListener(CC_CALLBACK_1(CCGameScene::puase,this));
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

void CCGameScene::updateheroScoreAndLive(const int& Hero, const int& score)
{
    char temp[64] = {0};
    sprintf(temp, "%d", score);
    (_rootNode->getChildByName("tilte")->getChildByName<ui::Text*>("Label_Score"))->setString(temp);
    sprintf(temp, "X %d", Hero);
    (_rootNode->getChildByName("tilte")->getChildByName<ui::Text*>("Label_live"))->setString(temp);
}

void CCGameScene::addRole(cocos2d::Node* Role)
{
    _rootNode->getChildByName("background")->addChild(Role);
}

cocos2d::Scene* CCGameScene::getGameScene()
{
    return getScene();
}

void CCGameScene::showPauseUI()
{
    if (!_pauseLayerShow)
    {
        addChild(_pauseLayer);
        _pauseLayerShow = true;
    }
}

void CCGameScene::hidePauseUI()
{
    if (_pauseLayerShow)
    {
        removeChild(_pauseLayer);
        _pauseLayerShow = false;
    }
}

Vector<cocos2d::Node*>& CCGameScene::getRole()
{
    return _rootNode->getChildByName("background")->getChildren();
}

void CCGameScene::back(Ref*)
{

}

void CCGameScene::restart(Ref*)
{

}

void CCGameScene::resume(Ref*)
{
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gameResume();
}

void CCGameScene::puase(Ref*)
{
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gamePause();
}


