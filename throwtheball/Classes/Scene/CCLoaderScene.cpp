#include "CCLoaderScene.h"
#include "cocostudio/CocoStudio.h"
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

void CCLoaderScene::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();

    addChild(_loading);
    //驾照音乐等资源

    std::thread loadRes(initResourceAndPlayer,this);
    loadRes.detach();
}

void CCLoaderScene::initResourceAndPlayer(CCLoaderScene* pthis)
{
    if (nullptr == pthis)
    {
        CCLOG("pthis is Null!");
        return ;
    }
    Sleep(3000);
    pthis->getScheduler()->performFunctionInCocosThread([=]{
        pthis->removeChild(pthis->_loading);
        pthis->addChild(pthis->_finish);
        pthis->_finish->runAction(Sequence::createWithTwoActions(FadeOut::create(0.0f), FadeIn::create(1.0f)));
        //没有阻塞函数通知是否完成某个动作，生硬点转换了
        auto hydrangea = pthis->_rootNode->getChildByName<Sprite*>("hydrangea");
        auto touchEvent = EventListenerTouchOneByOne::create();
        touchEvent->setSwallowTouches(true);
        touchEvent->onTouchBegan = CC_CALLBACK_2(CCLoaderScene::onHydrangeaTouchBegan, pthis);
        touchEvent->onTouchMoved = CC_CALLBACK_2(CCLoaderScene::onHydrangeaTouchMove, pthis);
        touchEvent->onTouchEnded = CC_CALLBACK_2(CCLoaderScene::onHydrangeaTouchEnded, pthis);
        hydrangea->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, hydrangea);
    });
}

bool CCLoaderScene::onHydrangeaTouchBegan(Touch* touch, Event* event)
{
    auto hydrangea = dynamic_cast<Sprite*>(event->getCurrentTarget());
    auto point = touch->getLocation();
    if (nullptr == hydrangea || 
        !hydrangea->getBoundingBox().containsPoint(point))
    {
        return false;
    }
    
    CCLOG("x:%f , y:%f", point.x, point.y);
    return true;
}

void CCLoaderScene::onHydrangeaTouchMove(Touch* touch, Event* event)
{
    auto hydrangea = dynamic_cast<Sprite*>(event->getCurrentTarget());
    hydrangea->setPositionY(touch->getLocation().y);
}

void CCLoaderScene::onHydrangeaTouchEnded(Touch* touch, Event* event)
{
    auto hydrangea = dynamic_cast<Sprite*>(event->getCurrentTarget());
    if (hydrangea->getPositionY() > 900)
    {
        CCLOG("switch scene!");
    }
    
}
