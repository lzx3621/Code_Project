#include "CCDefaultImageLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCDefaultImageLayer::CCDefaultImageLayer()
    :_rootNode(nullptr),
    _listNode(nullptr),
    _detailLayer(nullptr),
    _seclect(nullptr)
{
    CCLOG("CCDefaultImageLayer create");
}

CCDefaultImageLayer::~CCDefaultImageLayer()
{
    CC_SAFE_RELEASE_NULL(_listNode);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_detailLayer);
    CCLOG("CCDefaultImageLayer delete");
}

// on "init" you need to initialize your instance
bool CCDefaultImageLayer::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Layer/DefaultImage/defaultImage.csb");
    if (!Layer::init() ||
        nullptr == _rootNode )
    {
        return false;
    }
    setName("CCDefaultImageLayer");
    _rootNode->retain();
    addChild(_rootNode);
    _seclect = _rootNode->getChildByName("select");
    CC_SAFE_RETAIN(_seclect);
    auto pageView = _rootNode->getChildByName<ui::PageView*>("PageView");
    pageView->scrollToPage(0);
    pageView->addEventListener(CC_CALLBACK_2(CCDefaultImageLayer::PageViewCallback, this));

    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCDefaultImageLayer::onButtomCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_rootNode->getChildByName("back"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),_rootNode->getChildByName("confirm"));
    auto items = _rootNode->getChildByName("PageView")->getChildByName("page_1")->getChildren();
    for (auto& item : items)
    {
        auto enable = CCAppConfig::getInstance()->getLevelIsUnlock(item->getName())->asBool();
        if (enable)
        {
            auto event = CCSpriteButtomEvent::create();
            event->setPressScale(1.0f);
            event->onClick = CC_CALLBACK_1(CCDefaultImageLayer::selectedEvent, this);
            getEventDispatcher()->addEventListenerWithSceneGraphPriority(event ,item);
            auto skin = static_cast<cocostudio::ObjectExtensionData*>(item->getUserObject())->getCustomProperty();
            if (skin == CCAppConfig::getInstance()->getHeroSkinPath())
            {
                selectedEvent(item);
            }
        }
        setCheckBoxEnable(item, enable);
    }
    return true;
}

void CCDefaultImageLayer::selectedEvent(cocos2d::Node* target)
{
    if (nullptr != _seclect)
    {
        //如果已经选择了，那就是取消
        CCAudioHelper::getInstance()->playEffect(1);
        if (target != _seclect->getParent())
        {
            _seclect->removeFromParent();
            target->addChild(_seclect);
            _seclect->setVisible(true);
            CCAppConfig::getInstance()->setHeroSkinName(target->getName());
        }
    }
}

void CCDefaultImageLayer::setCheckBoxEnable(cocos2d::Node* item, bool enable)
{
    if (nullptr != item)
    {
        if (enable)
        {
            item->getChildByName("disable")->setVisible(false);
        }
        else
        {
            item->getChildByName("disable")->setVisible(true);
        }
    }
}

void CCDefaultImageLayer::onButtomCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    if ("back" == target->getName())
    {
        CCAudioHelper::getInstance()->playEffect(1);
        removeFromParent();
    }
    else if ("confirm" == target->getName())
    {
        if (_seclect->getParent() != _rootNode)
        {
            auto skin = static_cast<cocostudio::ObjectExtensionData*>(_seclect->getParent()->getUserObject())->getCustomProperty();
            CCAppConfig::getInstance()->setHeroSkinPath(skin);
            CCAppConfig::getInstance()->setHeroFace(SZFACEPATH);
        }
        removeFromParent();
        CCAudioHelper::getInstance()->playEffect(2);
    }
}

void CCDefaultImageLayer::PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event)
{
    auto curPageIndex = _rootNode->getChildByName<ui::PageView*>("PageView")->getCurPageIndex();
    auto PageCount  = _rootNode->getChildByName<ui::PageView*>("PageView")->getChildrenCount();
    CCLOG("CurPageIndex %d, PageCount %d", curPageIndex, PageCount);
    if (curPageIndex != 0 &&
        curPageIndex != (PageCount-1))
    {
        //中间
        _rootNode->getChildByName("direction_l_n")->setVisible(true);
        _rootNode->getChildByName("direction_r_n")->setVisible(true);
    }
    else
    {
        _rootNode->getChildByName("direction_l_n")->setVisible(true);
        _rootNode->getChildByName("direction_r_n")->setVisible(true);
        if (curPageIndex == 0)
        {
            //第一页
            _rootNode->getChildByName("direction_l_n")->setVisible(false);
        }
        //有可能同时存在
        if (curPageIndex == (PageCount-1))
        {
            //最后一页
            _rootNode->getChildByName("direction_r_n")->setVisible(false);
        }
    }
}


