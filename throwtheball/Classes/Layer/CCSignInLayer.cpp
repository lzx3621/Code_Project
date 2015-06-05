#include "CCSignInLayer.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "AppConfig/CCAppConfig.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCSignInLayer::CCSignInLayer()
    :_rootNode(nullptr),
    _getObject(nullptr)
{
    CCLOG("CCSignInLayer create");
}

CCSignInLayer::~CCSignInLayer()
{
    CC_SAFE_RELEASE_NULL(_getObject);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CCLOG("CCSignInLayer delete");
}

// on "init" you need to initialize your instance
bool CCSignInLayer::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Layer/SignIn/signIn.csb");
    if (!Layer::init() ||
        nullptr == _rootNode ||
        !initGetObject())
    {
        return false;
    }
    setName("CCSignInLayer");
    _rootNode->retain();
    addChild(_rootNode);
    schedule(CC_CALLBACK_1(CCSignInLayer::popThis, this),
        5.0f,
        "popThis");
    return true;
}


bool CCSignInLayer::initGetObject()
{
    _getObject = _rootNode->getChildByName("getobject");
    if (nullptr == _getObject)
    {
        CCLOGERROR("Layer/SignIn/GetObject/getobject.csb!");
        return false;
    }
    _getObject->retain();
    _getObject->setVisible(false);
    scheduleOnce([=](float){
        _getObject->setVisible(true);
        _getObject->runAction(
            Sequence::create(
            ScaleTo::create(0.15f, 1.25f),
            ScaleTo::create(0.1f, 1.0f),
            nullptr));
        CCAudioHelper::getInstance()->playEffect(3);
    }, 1.0f, "getObject");
    
    auto SignInDays = CCAppConfig::getInstance()->getSignInDays();
    if (CCAppConfig::getInstance()->checkYesterday())
    {
        CCAppConfig::getInstance()->setSignInDays(++SignInDays);
    }
    else if (!CCAppConfig::getInstance()->checkToday())
    {
        CCAppConfig::getInstance()->setSignInDays(SignInDays = 1);
    }
    auto Container =_rootNode->getChildByName("Container");
    if (nullptr == Container)
    {
        CCLOGERROR("no Container");
        return false;
    }
    if (Container->getChildrenCount() < SignInDays)
    {
        SignInDays = 1;
    }
    char Temp[32] = {0};
    auto num = 0;
    sprintf(Temp, "item_%d", SignInDays);
    auto item = Container->getChildByName(Temp);
    sscanf(static_cast<cocostudio::ObjectExtensionData*>(item->getUserObject())->getCustomProperty().c_str(),
        "%d_%s", &num, Temp);
    _getObject->getChildByName(Temp)->setVisible(true);
    _getObject->getChildByName<ui::TextBMFont*>("title")->setString(
        static_cast<cocostudio::ObjectExtensionData*>(item->getChildByName("title")->getUserObject())->getCustomProperty());
    return true;
}

void CCSignInLayer::popThis(float d)
{
    removeFromParent();
}

