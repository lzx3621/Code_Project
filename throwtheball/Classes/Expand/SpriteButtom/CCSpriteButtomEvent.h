#ifndef __SPRITEBUTTOMEVENT_H__
#define __SPRITEBUTTOMEVENT_H__
#include "cocos2d.h"

class CCSpriteButtomEvent : public cocos2d::EventListenerTouchOneByOne
{
    CCSpriteButtomEvent();
    ~CCSpriteButtomEvent();
public:
    CREATE_FUNC(CCSpriteButtomEvent);

    virtual bool init();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event);

    CCSpriteButtomEvent* clone() override;

public:
    std::function<void(cocos2d::Node*)> onClick;
    friend class cocos2d::EventDispatcher;
};
#endif __SPRITEBUTTOMEVENT_H__