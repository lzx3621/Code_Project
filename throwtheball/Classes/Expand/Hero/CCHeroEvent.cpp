#include "CCHeroEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "Role/CCHero.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;


CCHeroEvent::CCHeroEvent():
    _gameScene(nullptr)
{
}

CCHeroEvent::~CCHeroEvent()
{

}

bool CCHeroEvent::init()
{
    if (!EventListenerTouchOneByOne::init())
    {
        return false;
    }
    EventListenerTouchOneByOne::onTouchBegan      = CC_CALLBACK_2(CCHeroEvent::onTouchBegan, this);
    EventListenerTouchOneByOne::onTouchMoved      = CC_CALLBACK_2(CCHeroEvent::onTouchMoved, this);
    EventListenerTouchOneByOne::onTouchEnded      = CC_CALLBACK_2(CCHeroEvent::onTouchEnded, this);
    EventListenerTouchOneByOne::onTouchCancelled  = CC_CALLBACK_2(CCHeroEvent::onTouchCancelled, this);
    setSwallowTouches(true);
    return true;
}

bool CCHeroEvent::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto hero   = static_cast<CCHero*>(event->getCurrentTarget());
    if (hero == nullptr || CCAppConfig::getInstance()->getLevelName() != hero->getName())
    {
        return false;
    }
    _gameScene = hero->getScene();
    auto heroSize	= hero->getContentSize();
    auto locationInNode = hero->convertToNodeSpace(touch->getLocation());
    auto rect = Rect(0, 0, heroSize.width, heroSize.height);
    //是否在精灵上的点击,并且没有超出边界,浮点数不要判断=了
    if (nullptr != _gameScene && 
        rect.containsPoint(locationInNode))
    {
        hero->walk();
        CCAudioHelper::getInstance()->playEffect(8);
        auto apartLeftmin = heroSize.width*hero->getScale()/2;
        auto apartRightMax = _gameScene->getContentSize().width - (heroSize.width*hero->getScale()/2);
        if ((apartLeftmin > touch->getLocation().x))
        {
            //hero->setPositionX(apartLeftmin);
            hero->_pos.x = apartLeftmin;
        }
        else if (apartRightMax < touch->getLocation().x)
        {
            //hero->setPositionX(apartRightMax);
            hero->_pos.x = apartRightMax;
        }
        else
        {
            //hero->setPositionX(touch->getLocation().x);
            hero->_pos.x = touch->getLocation().x;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void CCHeroEvent::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto hero		= static_cast<CCHero*>(event->getCurrentTarget());
    auto heroSize	= hero->getContentSize();
    auto locationInNode = hero->convertToNodeSpace(touch->getLocation());
    auto rect = Rect(0, 0, heroSize.width, heroSize.height);
    if (nullptr != _gameScene &&
        rect.getMaxY() > locationInNode.y &&
        rect.getMinY() < locationInNode.y)
    {
        auto apartLeftmin = heroSize.width*hero->getScale()/2;
        auto apartRightMax = _gameScene->getContentSize().width - (heroSize.width*hero->getScale()/2);
        if ((apartLeftmin > touch->getLocation().x))
        {
            //hero->setPositionX(apartLeftmin);
            hero->_pos.x = apartLeftmin;
        }
        else if (apartRightMax < touch->getLocation().x)
        {
            //hero->setPositionX(apartRightMax);
            hero->_pos.x = apartRightMax;
        }
        else
        {
            //hero->setPositionX(touch->getLocation().x);
            hero->_pos.x = touch->getLocation().x;
        }
    }
}

CCHeroEvent* CCHeroEvent::clone()
{
    auto ret = new (std::nothrow) CCHeroEvent();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void CCHeroEvent::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event)
{
    static_cast<CCHero*>(event->getCurrentTarget())->stand();
}

void CCHeroEvent::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event)
{
    static_cast<CCHero*>(event->getCurrentTarget())->stand();
}
