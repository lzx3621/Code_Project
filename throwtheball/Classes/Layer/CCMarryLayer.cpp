#include "CCMarryLayer.h"
#include "cocostudio/CocoStudio.h"
#include "AppConfig/CCAppConfig.h"
#include "CCPhotoLayer.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCMarryLayer::CCMarryLayer()
    :_rootNode(nullptr),
    _getObject(nullptr)
{
    CCLOG("CCMarryLayer create");
}

CCMarryLayer::~CCMarryLayer()
{
    CC_SAFE_RELEASE_NULL(_getObject);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CCLOG("CCMarryLayer delete");
}

// on "init" you need to initialize your instance
bool CCMarryLayer::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Layer/Marry/marry.csb");
    if (!Layer::init() ||
        nullptr == _rootNode)
    {
        return false;
    }
    _rootNode->retain();
    auto listen = CCSpriteButtomEvent::create();
    listen->onClick = CC_CALLBACK_1(CCMarryLayer::onOpitonCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, 
        _rootNode->getChildByName("photo"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen->clone(), 
        _rootNode->getChildByName("level"));
    setBrideAndBridegroom(CCAppConfig::getInstance()->getCurrentScore());
    setName("CCMarryLayer");
    addChild(_rootNode);
    switchFace();
    return true;
}

void CCMarryLayer::switchFace()
{
    auto clipper = ClippingNode::create(Sprite::create(SZFACEPATH));
    clipper->setInverted(false);
    clipper->setAlphaThreshold(0);
    auto target= Sprite::create(CCAppConfig::getInstance()->getHeroFace());
    clipper->addChild(target);
    clipper->setScale(1.17f);
    clipper->setPosition(Point(150.0f,397.0f));
    _rootNode->getChildByName("bridegroom")->addChild(clipper);
}

void CCMarryLayer::onOpitonCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    CCAudioHelper::getInstance()->playEffect(1);
    if ("photo" == target->getName())
    {
        getParent()->addChild(CCPhotoLayer::create());
    }
    else if ("level" == target->getName())
    {
        removeFromParent();
    }
}

void CCMarryLayer::setBrideAndBridegroom(int score)
{
    std::string Bride("Sprite/Bride/"), Bridegroom("Sprite/Bridegroom/");
    Bridegroom += CCAppConfig::getInstance()->getLevelName() + ".png";
    Bride += CCAppConfig::getInstance()->getLevelName() + '/';
    auto brides = CCAppConfig::getInstance()->getBride(
        CCAppConfig::getInstance()->getLevelName())->asValueVector();
    if (score <= 2500)
    {
        Bride += "1.png";
        brides[0] = true;
    }
    else if (score >= 2501 && score <= 5000)
    {
        Bride += "2.png";
        brides[1] = true;
    }
    else if (score >= 5001 && score <= 7500)
    {
        Bride += "3.png";
        brides[2] = true;
    }
    else if (score >= 7501 && score <= 10000)
    {
        Bride += "4.png";
        brides[3] = true;
    }
    else if (score >= 10001 && score <= 12500)
    {
        Bride += "5.png";
        brides[4] = true;
    }
    else if (score >= 12501 && score <= 15000)
    {
        Bride += "6.png";
        brides[5] = true;
    }
    else if (score >= 15001 && score <= 15000)
    {
        Bride += "7.png";
        brides[6] = true;
    }
    else if (score >= 17501 && score <= 20000)
    {
        Bride += "8.png";
        brides[7] = true;
    }
    if (score > 20000)
    {
        Bride += "9.png";
        brides[8] = true;
    }
    CCAppConfig::getInstance()->setNewBride(true);
    auto bridegroom = CCAppConfig::getInstance()->getLevelName();
    CCLOG("bridegroom name:%s, get score: %d", bridegroom.c_str(), score);
    CCAppConfig::getInstance()->setBride(bridegroom, Value(brides));
    _rootNode->getChildByName<Sprite*>("bride")->setTexture(Bride);
    _rootNode->getChildByName<Sprite*>("bridegroom")->setTexture(Bridegroom);
}

void CCMarryLayer::onEnter()
{
    Layer::onEnter();
    CCAudioHelper::getInstance()->playMusic("marry");
}

void CCMarryLayer::onExit()
{
    Layer::onExit();
    CCAudioHelper::getInstance()->playMusic("normal");
}
