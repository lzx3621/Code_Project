#include "CCLoaderScene.h"
#include "cocostudio/CocoStudio.h"
#include "CCMenuScene.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCLoaderScene::CCLoaderScene()
    :_rootNode(nullptr),
    _loading(nullptr),
    _finish(nullptr),
    _originalPosition(Point::ZERO),
    _showOther(false),
    _finishok(false)
{
    CCLOG("CCLoaderScene create");
}

CCLoaderScene::~CCLoaderScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_loading);
    CC_SAFE_RELEASE_NULL(_finish);
    CCLOG("CCLoaderScene delete");
}

bool CCLoaderScene::init()
{
    _rootNode   = CSLoader::createNode("Layer/Load/load.csb");
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
    CCAudioHelper::getInstance()->playMusic("normal");
    return true;
}

bool CCLoaderScene::initloading()
{
    _loading = CSLoader::createNode("Layer/Load/loading.csb");
    if (nullptr == _loading)
    {
        CCLOGERROR("Layer/Load/loading.csb load failed!");
        return false;
    }
    _loading->retain();
    _loading->runAction(RepeatForever::create(
        Sequence::create(
        FadeOut::create(2.0f),
        CallFunc::create(CC_CALLBACK_0(CCLoaderScene::loadingFinish, this)),
        FadeIn::create(1.0f), 
        nullptr)));
    CCAudioHelper::getInstance()->preload();

    return true;
}

bool CCLoaderScene::initfinish()
{
    _finish = CSLoader::createNode("Layer/Load/finish.csb");
    if (nullptr == _finish)
    {
        CCLOGERROR("Layer/Load/loading.csb load failed!");
        return false;
    }
    _finish->retain();
    _finish->getChildByName("title")->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(1.0f), FadeIn::create(0.5f))));
    _finish->getChildByName("arrows_up")->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(1.0f), FadeIn::create(0.5f))));
    return true;
}

void CCLoaderScene::onEnterTransitionDidFinish()
{
    Node::onEnter();

    addChild(_loading);
    //驾照音乐等资源

    std::thread loadRes(initResourceAndPlayer,this);
    loadRes.detach();
}

void CCLoaderScene::initResourceAndPlayer(CCLoaderScene* pthis)
{
    if (nullptr == pthis)
    {
        CCLOGERROR("pthis is Null!");
        return ;
    }
    pthis->scheduleOnce([=](float){
        pthis->_finishok = true;
    },
        3.0f,
        "addFinish");
}

void CCLoaderScene::loadingFinish()
{
    if (_finishok)
    {
        removeChild(_loading);
        _loading->stopAllActions();
        addChild(_finish);
        //没有阻塞函数通知是否完成某个动作，生硬点转换了
        auto hydrangea = _rootNode->getChildByName<Sprite*>("hydrangea");
        auto touchEvent = EventListenerTouchOneByOne::create();
        touchEvent->setSwallowTouches(true);
        touchEvent->onTouchBegan = CC_CALLBACK_2(CCLoaderScene::onHydrangeaTouchBegan, this);
        touchEvent->onTouchMoved = CC_CALLBACK_2(CCLoaderScene::onHydrangeaTouchMove, this);
        hydrangea->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, hydrangea);
        _originalPosition = hydrangea->getPosition();
    }

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
    if (hydrangea->getPositionY() > touch->getLocation().y)
    {
        return ;
    }
    hydrangea->setPositionY(touch->getLocation().y);
    if (hydrangea->getPositionY() > 900 && !_showOther)
    {
        CCLOG("switch scene!");
        CCAudioHelper::getInstance()->playEffect(17);
        Director::getInstance()->replaceScene(CCMenuScene::create());
        _showOther = true;
    }
}


