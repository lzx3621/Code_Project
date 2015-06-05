#include "CCStoreLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCStoreLayer::CCStoreLayer()
    :_rootNode(nullptr),
    _storeNode(nullptr),
    _seclect(nullptr),
    _buyObjectOK(nullptr),
    _buyLevelOK(nullptr),
    _buyFailNotEnough(nullptr),
    _buyFailAlready(nullptr),
    _showPage(nullptr)
{
    CCLOG("CCStoreLayer create");
}

CCStoreLayer::~CCStoreLayer()
{
    CC_SAFE_RELEASE_NULL(_buyObjectOK);
    CC_SAFE_RELEASE_NULL(_buyLevelOK);
    CC_SAFE_RELEASE_NULL(_buyFailNotEnough);
    CC_SAFE_RELEASE_NULL(_buyFailAlready);
    CC_SAFE_RELEASE_NULL(_seclect);
    CC_SAFE_RELEASE_NULL(_storeNode);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CCLOG("CCStoreLayer delete");
}

// on "init" you need to initialize your instance
bool CCStoreLayer::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Layer/Store/store.csb");
    if (!Layer::init() ||
        nullptr == _rootNode ||
        !initStoreNode()||
        !initBuyObjectOK()||
        !initBuyLevelOK()||
        !initBuyFailNotEnough() ||
        !initBuyFailAlready())
    {
        return false;
    }
    setName("CCStoreLayer");
    _rootNode->retain();
    addChild(_rootNode);

    return true;
}

bool CCStoreLayer::initStoreNode()
{
    _storeNode = _rootNode->getChildByName("storeNode");
    if (nullptr == _storeNode)
    {
        CCLOGERROR("Layer/Store/store.csb load failed!");
        return false;
    }
    _seclect = _storeNode->getChildByName("select");
    CC_SAFE_RETAIN(_seclect);
    _storeNode->retain();
    auto pageView = _storeNode->getChildByName<ui::PageView*>("PageView_Object");
    pageView->setVisible(true);
    _showPage = pageView;
    pageView->addEventListener(CC_CALLBACK_2(CCStoreLayer::PageViewCallback, this));
    pageView->scrollToPage(0);
    addListent(pageView->getChildByName<ui::Layout*>("page_1"));
    addListent(pageView->getChildByName<ui::Layout*>("page_2"));
    pageView = _storeNode->getChildByName<ui::PageView*>("PageView_Level");
    pageView->setVisible(false);
    pageView->addEventListener(CC_CALLBACK_2(CCStoreLayer::PageViewCallback, this));
    pageView->scrollToPage(0);
    addListent(pageView->getChildByName<ui::Layout*>("page_1"));
    return initButtom();
}

bool CCStoreLayer::initButtom()
{
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onButtomCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _storeNode->getChildByName("back"));
    listener = listener->clone();
    listener->setPressScale(1.0f);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        listener, _storeNode->getChildByName("level"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        listener->clone(), _storeNode->getChildByName("object"));
    listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onConfirmBuy, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _storeNode->getChildByName("confirm"));
    listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::prePage, this);
    listener->setPressScale(1.0f);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _storeNode->getChildByName("direction_l_n"));
    listener = listener->clone();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::nextPage, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _storeNode->getChildByName("direction_r_n"));
    _storeNode->getChildByName("money")->getChildByName<ui::TextBMFont*>("num")->setString(
        Value(CCAppConfig::getInstance()->getMoney()).asString());
    _storeNode->getChildByName("object")->getChildByName("disable")->setVisible(true);
    _storeNode->getChildByName("level")->getChildByName("disable")->setVisible(false);
    return true;
}

bool CCStoreLayer::initBuyObjectOK()
{
    _buyObjectOK = CSLoader::createNode("Layer/Store/Buy/buyok_object.csb");
    if (nullptr == _buyObjectOK)
    {
        CCLOGERROR("Layer/Store/Buy/buyok_object.csb load failed!");
        return false;
    }
    CC_SAFE_RETAIN(_buyObjectOK);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onConfirm, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_buyObjectOK->getChildByName("confirm"));
    return true;
}

bool CCStoreLayer::initBuyLevelOK()
{
    _buyLevelOK = CSLoader::createNode("Layer/Store/Buy/buyok_level.csb");
    if (nullptr == _buyLevelOK)
    {
        CCLOGERROR("Layer/Store/Buy/buyok_level.csb load failed!");
        return false;
    }
    CC_SAFE_RETAIN(_buyLevelOK);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onConfirm, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_buyLevelOK->getChildByName("confirm"));
    return true;
}
bool CCStoreLayer::initBuyFailNotEnough()
{
    _buyFailNotEnough = CSLoader::createNode("Layer/Store/Buy/buyfalse_notenough.csb");
    if (nullptr == _buyFailNotEnough)
    {
        CCLOGERROR("Layer/Store/Buy/buyfalse_notenough.csb load failed!");
        return false;
    }
    CC_SAFE_RETAIN(_buyFailNotEnough);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onConfirm, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_buyFailNotEnough->getChildByName("confirm"));
    return true;
}

bool CCStoreLayer::initBuyFailAlready()
{
    _buyFailAlready = CSLoader::createNode("Layer/Store/Buy/buyfalse_already.csb");
    if (nullptr == _buyFailAlready)
    {
        CCLOGERROR("Layer/Store/Buy/buyfalse_notenough.csb load failed!");
        return false;
    }
    CC_SAFE_RETAIN(_buyFailAlready);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreLayer::onConfirm, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_buyFailAlready->getChildByName("confirm"));
    return true;
}

void CCStoreLayer::addListent(cocos2d::ui::Layout* page)
{
    if (nullptr == page)
    {
        return ;
    }
    auto children = page->getChildren();
    for (auto& item : children)
    {
        auto event = CCSpriteButtomEvent::create();
        event->setSwallowTouches(false);
        event->onClick = CC_CALLBACK_1(CCStoreLayer::selectedEvent, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(event ,item);
    }
}

void CCStoreLayer::selectedEvent(cocos2d::Node* target)
{
    if (nullptr != _seclect)
    {
        //如果已经选择了，那就是取消
        if (target == _seclect->getParent())
        {
            _seclect->removeFromParent();
            _storeNode->addChild(_seclect);
            _seclect->setVisible(false);
        }
        else
        {
            CCAudioHelper::getInstance()->playEffect(3);
            _seclect->removeFromParent();
            target->addChild(_seclect);
            _seclect->setVisible(true);
        }
    }
}


void CCStoreLayer::onButtomCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    CCAudioHelper::getInstance()->playEffect(1);
    if ("back" == target->getName())
    {
        removeFromParent();
    }
    else if ("object" == target->getName())
    {
        //PageView_object
        _storeNode->getChildByName("level")->getChildByName("disable")->setVisible(false);
        target->getChildByName("disable")->setVisible(true);
        _storeNode->getChildByName("PageView_Level")->setVisible(false);
        _showPage = _storeNode->getChildByName<ui::PageView*>("PageView_Object");
        _showPage->setVisible(true);
        _showPage->scrollToPage(_showPage->getCurPageIndex());
    }
    else if ("level" == target->getName())
    {
        //PageView_Level
        _storeNode->getChildByName("PageView_Object")->setVisible(false);
        _storeNode->getChildByName("object")->getChildByName("disable")->setVisible(false);
        target->getChildByName("disable")->setVisible(true);
        _showPage = _storeNode->getChildByName<ui::PageView*>("PageView_Level");
        _showPage->setVisible(true);
        _showPage->scrollToPage(_showPage->getCurPageIndex());
    }
}

void CCStoreLayer::PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event)
{
    auto curPageIndex = _showPage->getCurPageIndex();
    auto PageCount  = _showPage->getChildrenCount();
    CCLOG("CurPageIndex %d, PageCount %d", curPageIndex, PageCount);
    if (curPageIndex != 0 &&
        curPageIndex != (PageCount-1))
    {
        //中间
        _storeNode->getChildByName("direction_l_n")->setVisible(true);
        _storeNode->getChildByName("direction_r_n")->setVisible(true);
    }
    else
    {
        _storeNode->getChildByName("direction_l_n")->setVisible(true);
        _storeNode->getChildByName("direction_r_n")->setVisible(true);
        if (curPageIndex == 0)
        {
            //第一页
            _storeNode->getChildByName("direction_l_n")->setVisible(false);
        }
        //有可能同时存在
        if (curPageIndex == (PageCount-1))
        {
            //最后一页
            _storeNode->getChildByName("direction_r_n")->setVisible(false);
        }
    }
}

void CCStoreLayer::onConfirmBuy(cocos2d::Node*)
{
    auto beSelect = _seclect->getParent();
    CCAudioHelper::getInstance()->playEffect(2);
    if (beSelect != _storeNode)
    {
        char name[20] = {0};
        auto num = 0;
        auto hold = CCAppConfig::getInstance()->getMoney();
        auto cost = 0;
        sscanf(beSelect->getName().c_str(),"%d_%s", &num, name);
        sscanf(static_cast<cocostudio::ObjectExtensionData*>(
            beSelect->getUserObject())->getCustomProperty().c_str(),
            "%d", &cost);
        if (hold > cost)
        {
            if (0 == num || 
                0 == strcmp(name,""))
            {
                sscanf(beSelect->getName().c_str(),"%s", name);
                if (CCAppConfig::getInstance()->getLevelIsUnlock(name)->asBool())
                {

                    addChild(_buyFailAlready);
                }
                else
                {
                    //购买成功
                    CCAppConfig::getInstance()->setMoney(hold - cost);
                    _storeNode->getChildByName("money")->getChildByName<ui::TextBMFont*>("num")->setString(
                        Value(CCAppConfig::getInstance()->getMoney()).asString());
                    CCAppConfig::getInstance()->setLevelIsUnlock(name, Value(true));
                    addChild(_buyLevelOK);
                }
                return ;
            }
            //购买成功
            CCAppConfig::getInstance()->setMoney(hold - cost);
            _storeNode->getChildByName("money")->getChildByName<ui::TextBMFont*>("num")->setString(
                Value(CCAppConfig::getInstance()->getMoney()).asString());
            addChild(_buyObjectOK);
            //设置显示的物品和数量
            showBuyObject(name, num);
            if (0 == strcmp(name, "fan"))
            {
                auto numHold = CCAppConfig::getInstance()->getObjectFan();
                CCAppConfig::getInstance()->setObjectFan(numHold+num);
            }
            else if (0 == strcmp(name, "clock"))
            {
                auto numHold = CCAppConfig::getInstance()->getObjectClock();
                CCAppConfig::getInstance()->setObjectClock(numHold+num);
            }
        }
        else
        {
            CCAudioHelper::getInstance()->playEffect(14);
            //购买失败
            addChild(_buyFailNotEnough);
        }
    }
}

void CCStoreLayer::onConfirm(Node* target)
{
    if (_buyFailNotEnough == target->getParent())
    {
        CCAudioHelper::getInstance()->playEffect(1);
    }
    else if (_buyObjectOK == target->getParent())
    {
        CCAudioHelper::getInstance()->playEffect(5);
    }
    target->getParent()->removeFromParent();
}

void CCStoreLayer::showBuyObject(const char * name, int &num)
{
    if (nullptr != _buyObjectOK)
    {
        std::stringstream string;
        string << "x " << num;
        _buyObjectOK->getChildByName<ui::TextBMFont*>("num")->setString(string.str());
        for (auto& child: _buyObjectOK->getChildByName("object")->getChildren())
        {
            if (child->getName() == name)
            {
                child->setVisible(true);
            }
            else
            {
                child->setVisible(false);
            }
        }
    }
}

void CCStoreLayer::nextPage(cocos2d::Node*)
{
    if (nullptr != _showPage)
    {
        CCAudioHelper::getInstance()->playEffect(1);
        auto curPageIndex = _showPage->getCurPageIndex();
        auto PageCount  = _showPage->getChildrenCount();
        if (++curPageIndex < PageCount)
        {
            _showPage->scrollToPage(curPageIndex);
        }
    }
}

void CCStoreLayer::prePage(cocos2d::Node*)
{
    if (nullptr != _showPage)
    {
        CCAudioHelper::getInstance()->playEffect(1);
        auto curPageIndex = _showPage->getCurPageIndex();
        auto PageCount  = _showPage->getChildrenCount();
        if (--curPageIndex >= 0)
        {
            _showPage->scrollToPage(curPageIndex);
        }
    }
}

void CCStoreLayer::switchPage(cocos2d::Node* target)
{

}

