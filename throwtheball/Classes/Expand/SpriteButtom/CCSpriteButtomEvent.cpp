#include "CCSpriteButtomEvent.h"
USING_NS_CC;


CCSpriteButtomEvent::CCSpriteButtomEvent()
{
    onClick = nullptr;
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
    return true;
}

bool CCSpriteButtomEvent::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto target = event->getCurrentTarget();
    if (target &&
        target->getBoundingBox().containsPoint(touch->getLocation()))
    {
        target->setScaleX(target->getScaleX()*0.8);
        target->setScaleY(target->getScaleY()*0.8);
        target->setScaleZ(target->getScaleZ()*0.8);
        return true;
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
    if (nullptr != target)
    {
        //ScaleTo::create();
        target->setScaleX(target->getScaleX()/0.8);
        target->setScaleY(target->getScaleY()/0.8);
        target->setScaleZ(target->getScaleZ()/0.8);
        if (nullptr != onClick && target->getBoundingBox().containsPoint(touch->getLocation()))
        {
            CCLOG("onClick");
            onClick;
        }
    }
}

void CCSpriteButtomEvent::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event)
{
    auto target = event->getCurrentTarget();
    if (nullptr != target)
    {
        //ScaleTo::create();
        target->setScaleX(target->getScaleX()/0.8);
        target->setScaleY(target->getScaleY()/0.8);
        target->setScaleZ(target->getScaleZ()/0.8);
    }
}

CCSpriteButtomEvent* CCSpriteButtomEvent::clone()
{
    auto ret = new (std::nothrow) CCSpriteButtomEvent();
    if (ret && ret->init())
    {
        ret->autorelease();

        ret->onClick = onClick;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}
