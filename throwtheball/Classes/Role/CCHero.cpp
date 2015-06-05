#include "CCHero.h"
#include "Adapter/CCHeroAdapterOfPhysics.h"
#include "Adapter/CCSupportAdapterOfPhysics.h"
#include "AppConfig/CCAppConfig.h"
#include "Expand/Hero/CCHeroEvent.h"
#include "CCSupport.h"


USING_NS_CC;

using namespace cocostudio::timeline;


bool CCHero::init()
{
    if (!SuperRole::init() || 
        !Sprite::init() ||
        !initFromCsb())
    {
        CCLOGERROR("CCHero faild");
        return false;
    }

    setName(CCAppConfig::getInstance()->getLevelName());
    //return true;
    auto physicalBody = PhysicsBody::createBox(getBoundingBox().size, PhysicsMaterial(10.0f, 0.0f, 0.0F));
    //此处设置主角被所有东西碰撞，但下落物体自己不碰撞
    if (nullptr != physicalBody)
    {
        physicalBody->setCategoryBitmask(1);
        physicalBody->setContactTestBitmask(2);
        physicalBody->setCollisionBitmask(1);
        physicalBody->setDynamic(false);
        setPhysicsBody(physicalBody);
    }
    //只注册一次，不要多次注册，不然会引起充分删除崩溃
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(CCHero::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(CCHeroEvent::create(), this);
    return true;
}

bool CCHero::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto ptr_NodeA = contact.getShapeA()->getBody()->getNode();
    auto ptr_NodeB = contact.getShapeB()->getBody()->getNode();
    if (ptr_NodeA && ptr_NodeB)
    {
        CCLOG("CCHero ptr_NodeA Name: %s, ptr_NodeB: %s",
            ptr_NodeA->getName().c_str(),
            ptr_NodeB->getName().c_str());
    }
    auto pthis = (ptr_NodeA == this)?this:(ptr_NodeB == this?this:nullptr);
    auto support = dynamic_cast<CCSupport*>((ptr_NodeA && ptr_NodeA != this)?ptr_NodeA:ptr_NodeB);
    if (nullptr == support && nullptr == pthis)
    {

        return true;
    }
    //碰撞配角1
    auto heroAdapet     = dynamic_cast<CCHeroAdapter*>(CCHeroAdapterOfPhysics::create(this));
    auto SupportAdapet  = dynamic_cast<CCSupportAdapter*>(CCSupportAdapterOfPhysics::create(support));
    if (nullptr != heroAdapet &&
        nullptr != SupportAdapet &&
        nullptr != heroAdapet->s_onHeroContact)
    {
        CCLOG("get");
        _armature->getAnimation()->play("get");
        heroAdapet->s_onHeroContact(*heroAdapet,*SupportAdapet);
    }
    CC_SAFE_DELETE(heroAdapet);
    CC_SAFE_DELETE(SupportAdapet);
    //返回ture表示无碰撞
    return true;
}

void CCHero::update(float delta)
{
    Sprite::update(delta);
    if (_pos != Point::ZERO &&
        getPositionX() != _pos.x)
    {
        Sprite::setPositionX(_pos.x);
    }
}

void CCHero::onEnter()
{
    Sprite::onEnter();
    scheduleUpdate();
}

bool CCHero::initFromCsb()
{
    auto skinPath = CCAppConfig::getInstance()->getHeroSkinPath();
    auto loader = CSLoader::createNode("Sprite/HeroArmature/heroArmature.csb")
        ->getChildByName(CCAppConfig::getInstance()->getHeroSkinName());
    _armature = loader->getChildByName<cocostudio::Armature*>("Armature");
    _armature->retain();
    _armature->removeFromParent();
    if ("Sprite/Hero_big/face.png" 
        != CCAppConfig::getInstance()->getHeroFace())
    {
        switchFace();
    }
    addChild(_armature);
    setAnchorPoint(loader->getAnchorPoint());
    setContentSize(loader->getContentSize());
    setScaleX(loader->getScaleX());
    setScaleY(loader->getScaleY());
    setScaleZ(loader->getScaleZ());
    _armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(CCHero::getObjectCallBack,this)); 
    //CC_SAFE_RELEASE(_armature);
    return true;
}

CCHero::~CCHero()
{
    CC_SAFE_RELEASE_NULL(_armature);
}

void CCHero::walk()
{
    if (_currPlay != "walk")
    {
        _currPlay = "walk";
        CCLOG("walk");
        _armature->getAnimation()->play("walk");
    }
}

void CCHero::get()
{
    if (_currPlay != "get")
    {
        _currPlay = "get";
        CCLOG("get");
        _armature->getAnimation()->play("get");
    }
}

void CCHero::stand()
{
    if (_currPlay != "huishou")
    {
        _currPlay = "huishou";
        CCLOG("huishou");
        _armature->getAnimation()->play("huishou");
    }
}

void CCHero::getObjectCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
    if (armature == _armature &&
        cocostudio::MovementEventType::LOOP_COMPLETE == movementType)
    {
        if (movementID == "get" && !_currPlay.empty())
        {
            armature->getAnimation()->play(_currPlay);
        }
    }
}

void CCHero::pause(void)
{
    Sprite::pause();
    _armature->getAnimation()->gotoAndPause(0);
}

void CCHero::resume(void)
{
    Sprite::resume();
    _armature->getAnimation()->resume();
}
void CCHero::switchFace()
{
    schedule([=](float){
    auto facePath = CCAppConfig::getInstance()->getHeroFace();
    if (FileUtils::getInstance()->isFileExist(facePath))
    {
        auto clipper = ClippingNode::create(Sprite::create(SZFACEPATH));
        clipper->setInverted(false);
        clipper->setAlphaThreshold(0);
        Director::getInstance()->getTextureCache()->reloadTexture(facePath);
        auto target= Sprite::create(facePath);
        target->setRotation(90.0f);
        clipper->addChild(target);
        clipper->setScale(0.76f);
        auto x = -3.5;
        auto y = 63;
        clipper->setPosition(Point(x,y));
        _armature->getBone("face")->addDisplay(clipper,0);
        unschedule("checkTexture");
    }
    },"checkTexture");
}
