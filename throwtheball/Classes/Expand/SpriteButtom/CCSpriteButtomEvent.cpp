#include "CCSpriteButtomEvent.h"
USING_NS_CC;


CCSpriteButtomEvent::CCSpriteButtomEvent():
    _pressScale(0.8f),
    onClick(nullptr)
{
}

CCSpriteButtomEvent::~CCSpriteButtomEvent()
{

}

bool CCSpriteButtomEvent::init()
{
    if (!EventListenerTouchOneByOne::init())
    {
        return false;
    }
    EventListenerTouchOneByOne::onTouchBegan      = CC_CALLBACK_2(CCSpriteButtomEvent::onTouchBegan, this);
    EventListenerTouchOneByOne::onTouchMoved      = CC_CALLBACK_2(CCSpriteButtomEvent::onTouchMoved, this);
    EventListenerTouchOneByOne::onTouchEnded      = CC_CALLBACK_2(CCSpriteButtomEvent::onTouchEnded, this);
    EventListenerTouchOneByOne::onTouchCancelled  = CC_CALLBACK_2(CCSpriteButtomEvent::onTouchCancelled, this);
    setSwallowTouches(true);
    return true;
}

bool CCSpriteButtomEvent::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto target = event->getCurrentTarget();

    if (nullptr != target && target->isVisible())
    {
        auto locationInNode = target->convertToNodeSpace(touch->getLocation());
        auto s = target->getContentSize();
        auto rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            target->setScaleX(target->getScaleX()*_pressScale);
            target->setScaleY(target->getScaleY()*_pressScale);
            target->setScaleZ(target->getScaleZ()*_pressScale);
            return true;
        }
        //target->getBoundingBox().containsPoint(target->convertToWorldSpace(touch->getLocation())))
        
    }
    return false;
}

void CCSpriteButtomEvent::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return ;
}

void CCSpriteButtomEvent::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event)
{
    auto target = event->getCurrentTarget();
    if (nullptr != target && target->isVisible())
    {
        //ScaleTo::create();
        target->setScaleX(target->getScaleX()/_pressScale);
        target->setScaleY(target->getScaleY()/_pressScale);
        target->setScaleZ(target->getScaleZ()/_pressScale);

        auto locationInNode = target->convertToNodeSpace(touch->getLocation());
        auto s = target->getContentSize();
        auto rect = Rect(0, 0, s.width, s.height);
        if (nullptr != onClick && rect.containsPoint(locationInNode))
        {
            onClick(target);
        }
    }
}

void CCSpriteButtomEvent::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event)
{
    auto target = event->getCurrentTarget();
    if (nullptr != target && target->isVisible())
    {
        //ScaleTo::create();
        target->setScaleX(target->getScaleX()/_pressScale);
        target->setScaleY(target->getScaleY()/_pressScale);
        target->setScaleZ(target->getScaleZ()/_pressScale);
    }
}

CCSpriteButtomEvent* CCSpriteButtomEvent::clone()
{
    auto ret = new (std::nothrow) CCSpriteButtomEvent();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->_pressScale = _pressScale;
        ret->onClick = onClick;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
