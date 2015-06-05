#ifndef __SPRITEHEROEVENT_H__
#define __SPRITEHEROEVENT_H__
#include "cocos2d.h"

class CCHeroEvent : public cocos2d::EventListenerTouchOneByOne
{
    CCHeroEvent();
    ~CCHeroEvent();
public:
    CREATE_FUNC(CCHeroEvent);

    virtual bool init();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event);
public:
    CCHeroEvent* clone() override;
private:
    cocos2d::Scene *_gameScene;
    friend class cocos2d::EventDispatcher;
};
#endif /*__SPRITEHEROEVENT_H__*/