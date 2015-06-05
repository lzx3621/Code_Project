#include "CCMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "Layer/CCSelectLevelLayer.h"
#include "Layer/CCSignInLayer.h"
#include "AppConfig/CCAppConfig.h"
#include "Layer/CCMarryLayer.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCMenuScene::CCMenuScene()
    :_rootNode(nullptr)
{
    _layers.clear();
    CCLOG("CCMenuScene create");
}

CCMenuScene::~CCMenuScene()
{
    CCAppConfig::getInstance()->commit();
    CC_SAFE_RELEASE_NULL(_rootNode);
    _layers.clear();
    CCLOG("CCMenuScene delete");
}

// on "init" you need to initialize your instance
bool CCMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Layer/Menu/menu.csb");
    if (!Scene::init() ||
        nullptr == _rootNode)
    {
        return false;
    }
    setName("CCMenuScene");
    _rootNode->retain();
    Scene::addChild(_rootNode);
    addChild(CCSelectLevelLayer::create());
    if (CCAppConfig::getInstance()->checkYesterday())
    {
        addChild(CCSignInLayer::create());
    }
    return true;
}

//如果是图层就吧当前图层压栈
void CCMenuScene::addChild(cocos2d::Node* child)
{
    auto layer = dynamic_cast<Layer*>(child);
    if (nullptr != layer)
    {
        if (!_layers.empty())
        {
            Scene::removeChild(_layers.back());
        }
        _layers.pushBack(layer);
    }
    Scene::addChild(child);
}

//图层的话，去掉最上面的，显示栈中下一个
void CCMenuScene::removeChild(Node* child, bool cleanup /*= true*/)
{
    auto layer = dynamic_cast<Layer*>(child);
    if (nullptr != layer)
    {
        if (!_layers.empty() &&
            child == _layers.back())
        {
            _layers.popBack();
            if (!_layers.empty())
            {
                Scene::addChild(_layers.back());
            }
        }
    }
    Scene::removeChild(child, cleanup);
}

void CCMenuScene::onEnter()
{
    Scene::onEnter();
    if (CCAppConfig::getInstance()->getShowMarry())
    {
        addChild(CCMarryLayer::create());
        CCAppConfig::getInstance()->setShowMarry(false);
    }
}
