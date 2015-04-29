#include "CCLoaderScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "./Rule/CCNormalRule.h"
#include "ui/UITextBMFont.h"

USING_NS_CC;

using namespace cocostudio::timeline;

CCLoaderScene::CCLoaderScene()
    :_rootNode(nullptr),
    _loading(nullptr),
    _finish(nullptr)
{

}

CCLoaderScene::~CCLoaderScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_loading);
    CC_SAFE_RELEASE_NULL(_finish);
}

Scene* CCLoaderScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    if (nullptr != scene)
    {
        auto layer = CCLoaderScene::create();
        if (nullptr != layer)
        {
            scene->addChild(layer);
            return scene;
        }
    }
    return nullptr;
}

// on "init" you need to initialize your instance
bool CCLoaderScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Scene/Load/load.csb");
    if (!Scene::init() ||
        nullptr == _rootNode ||
        !initloading() ||
        !initfinish())
    {
        return false;
    }
    setName("CCLoaderScene");
    _rootNode->retain();
    
    addChild(_rootNode);
    addChild(_finish);

    return true;
}

bool CCLoaderScene::initloading()
{
    _loading = CSLoader::createNode("Scene/Load/loading.csb");
    if (nullptr == _loading)
    {
        CCLOG("Scene/Load/loading.csb load failed!");
        return false;
    }
    _loading->retain();
    _loading->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(2.0f), FadeIn::create(1.0f))));
    return true;
}

bool CCLoaderScene::initfinish()
{
    _finish = CSLoader::createNode("Scene/Load/finish.csb");
    if (nullptr == _finish)
    {
        CCLOG("Scene/Load/loading.csb load failed!");
        return false;
    }
    _finish->retain();
    _finish->getChildByName("title")->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(1.0f), FadeIn::create(0.5f))));
    _finish->getChildByName("arrows_up")->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(1.0f), FadeIn::create(0.5f))));
    return true;
}
