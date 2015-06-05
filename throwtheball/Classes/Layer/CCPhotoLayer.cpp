#include "CCPhotoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "ui/UIPageView.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCPhotoLayer::CCPhotoLayer()
    :_rootNode(nullptr),
    _scrollView(nullptr),
    _bridegroom(nullptr),
    COLUMN(3),
    ROWDIST(30),
    _seclect(nullptr),
    _bride(nullptr)
{
    CCLOG("CCPhotoLayer create");
}

CCPhotoLayer::~CCPhotoLayer()
{
    CC_SAFE_RELEASE_NULL(_scrollView);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_bridegroom);
    CC_SAFE_RELEASE_NULL(_bride);
    CC_SAFE_RELEASE_NULL(_seclect);
    CCSpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Layer/Photo/Bride/bride.plist");
    CCLOG("CCPhotoLayer delete");
}

// on "init" you need to initialize your instance
bool CCPhotoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("Layer/Photo/Bride/bride.plist");
    _rootNode   = CSLoader::createNode("Layer/Photo/photo.csb");
    if (!Layer::init() ||
        nullptr == _rootNode ||
        !initScrollView())
    {
        return false;
    }
    setName("CCPhotoLayer");
    CC_SAFE_RETAIN(_rootNode);
    addChild(_rootNode);
    _seclect = _rootNode->getChildByName("select");
    _bridegroom = _rootNode->getChildByName<Sprite*>("bridegroom");
    _bride  = _rootNode->getChildByName<Sprite*>("bride");
    if (nullptr == _seclect ||
        nullptr == _bridegroom ||
        nullptr == _bride)
    {
        return false; 
    }
    CC_SAFE_RETAIN(_seclect);
    CC_SAFE_RETAIN(_bridegroom);
    CC_SAFE_RETAIN(_bride);
    CCAppConfig::getInstance()->setNewBride(false);
    auto event = CCSpriteButtomEvent::create();
    event->onClick = CC_CALLBACK_1(CCPhotoLayer::onButtomCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, _rootNode->getChildByName("back"));
    switchFace();
    return true;
}


bool CCPhotoLayer::initScrollView()
{
    _scrollView = _rootNode->getChildByName("ScrollView");
    if (nullptr == _scrollView)
    {
        CCLOGERROR("ScrollView null!");
        return false;
    }
    _scrollView->retain();
    auto container = _scrollView->getChildByName("container");
    auto children = container->getChildren();
    auto itemSize = (*children.begin())->getContentSize();
    auto containerSize = container->getContentSize();
    auto itemCount = container->getChildrenCount();
    auto columnDIST = (containerSize.width - itemSize.width*COLUMN)/(COLUMN+1);
    Vector<Node*> Enable, Disable;
    getVector(Enable, Disable);
    auto iterEnable = Enable.begin();
    auto iterDisable = Disable.begin();
    auto x = 0.0f;
    auto y = containerSize.height + (itemSize.height/2);
    for (int row = 0; row < itemCount/COLUMN; row++)
    {
        y -=  (itemSize.height + ROWDIST);
        x = -(itemSize.width/2);
        for (int col = 0; col < COLUMN; col++)
        {
            x += itemSize.width + columnDIST;
            if (iterEnable != Enable.end())
            {
                (*(iterEnable++))->setPosition(x,y);
            }
            else if (iterDisable != Disable.end())
            {
                (*(iterDisable++))->setPosition(x,y);
            }
        }
    }
    return true;
}

void CCPhotoLayer::getVector(Vector<Node*> &outEnable, Vector<Node*> &outDisable)
{
    ValueVector  waiters(CCAppConfig::getInstance()->getBride("waiter")->asValueVector());
    ValueVector  scholars(CCAppConfig::getInstance()->getBride("scholar")->asValueVector());
    ValueVector  generals(CCAppConfig::getInstance()->getBride("general")->asValueVector());
    ValueVector  caterans(CCAppConfig::getInstance()->getBride("cateran")->asValueVector());
    auto container = _scrollView->getChildByName("container");
    Node *item = nullptr;
    bool isEnable;
    char temp[20] = {0};
    for (int i = 1; i < 10; i++)
    {
        sprintf(temp, "waiter_%d", i);
        item = container->getChildByName(temp);
        if (nullptr != item)
        {
            if (waiters[i-1].asBool())
            {
                outEnable.pushBack(item);
                isEnable = true;
            }
            else
            {
                outDisable.pushBack(item);
                isEnable = false;
            }
            setItemEnable(item, isEnable);
        }
        sprintf(temp, "scholar_%d", i);
        item = container->getChildByName(temp);
        if (nullptr != item)
        {
            if (scholars[i-1].asBool())
            {
                outEnable.pushBack(item);
                isEnable = true;
            }
            else
            {
                outDisable.pushBack(item);
                isEnable = false;
            }
            setItemEnable(item, isEnable);
        }
        sprintf(temp, "cateran_%d", i);
        item = container->getChildByName(temp);
        if (nullptr != item)
        {
            if (caterans[i-1].asBool())
            {
                outEnable.pushBack(item);
                isEnable = true;
            }
            else
            {
                outDisable.pushBack(item);
                isEnable = false;
            }
            setItemEnable(item, isEnable);
        }
        sprintf(temp, "general_%d", i);
        item = container->getChildByName(temp);
        if (nullptr != item)
        {
            if (generals[i-1].asBool())
            {
                outEnable.pushBack(item);
                isEnable = true;
            }
            else
            {
                outDisable.pushBack(item);
                isEnable = false;
            }
            setItemEnable(item, isEnable);
        }
    }
}

void CCPhotoLayer::selectedEvent(cocos2d::Node* target)
{
    if (nullptr != _seclect)
    {
        if (nullptr != target &&
            _seclect->getParent() != target)
        {
            if (std::string::npos != target->getName().find('9'))
            {
                CCAudioHelper::getInstance()->playEffect(13);
            }
            else
            {
                CCAudioHelper::getInstance()->playEffect(1);
            }
            _seclect->removeFromParent();
            target->addChild(_seclect);
            _seclect->setVisible(true);
            auto bridegroom = 
                static_cast<cocostudio::ObjectExtensionData*>(target->getChildByName("face")->getUserObject())->getCustomProperty();
            auto bride = 
                static_cast<cocostudio::ObjectExtensionData*>(target->getChildByName("face")->getChildByName("Image")->getUserObject())
                ->getCustomProperty();
            CCLOG("bridegroom :%s, bride:%s", bridegroom.c_str(), bride.c_str());
            if (!bride.empty())
            {
                _bride->setVisible(true);
                _bride->setTexture(bride);
                //_bride->setSpriteFrame(bride);
            }
            if (!bridegroom.empty())
            {
                _bridegroom->setVisible(true);
                _bridegroom->setTexture(bridegroom);
                //_bridegroom->setSpriteFrame(bridegroom);
            }
        }
    }
}

void CCPhotoLayer::setItemEnable(cocos2d::Node* item, bool enable)
{
    if (nullptr != item)
    {
        if (enable)
        {
            item->getChildByName("face")->setVisible(true);
            item->getChildByName("disable")->setVisible(false);
            auto event = CCSpriteButtomEvent::create();
            event->setPressScale(1.0f);
            event->setSwallowTouches(false);
            event->onClick = CC_CALLBACK_1(CCPhotoLayer::selectedEvent, this);
            getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, item);
        }
        else
        {
            item->getChildByName("face")->setVisible(false);
            item->getChildByName("disable")->setVisible(true);
        }
    }
}

void CCPhotoLayer::onButtomCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    if ("back" == target->getName())
    {
        CCAudioHelper::getInstance()->playEffect(1);
        removeFromParent();
    }
}

void CCPhotoLayer::switchFace()
{
    auto clipper = ClippingNode::create(Sprite::create(SZFACEPATH));
    clipper->setInverted(false);
    clipper->setAlphaThreshold(0);
    auto path = CCAppConfig::getInstance()->getHeroFace();
    auto target= Sprite::create(CCAppConfig::getInstance()->getHeroFace());
    clipper->addChild(target);
    clipper->setScale(1.17f);
    clipper->setPosition(Point(150.0f,397.0f));
    _rootNode->getChildByName("bridegroom")->addChild(clipper);
}
