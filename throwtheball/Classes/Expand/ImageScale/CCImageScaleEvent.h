#ifndef __IMAGESCALEEVENT_H__
#define __IMAGESCALEEVENT_H__
#include "cocos2d.h"

class CCImageScaleEvent : public cocos2d::EventListenerTouchAllAtOnce
{
    CCImageScaleEvent();
    ~CCImageScaleEvent();
public:
    CREATE_FUNC(CCImageScaleEvent);

    virtual bool init();

    void onTouchBegan(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
    void onTouchMoved(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
    void onTouchEnded(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
    void onTouchCancelled(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
public:
    CC_SYNTHESIZE(cocos2d::Node*, _target, Target);
    CC_SYNTHESIZE(cocos2d::Node*, _listenNode, ListenNode);
    CCImageScaleEvent* clone() override;
private:
    bool    _isMove;
    float   _DistOld;
    float   _DistNew;
    friend class cocos2d::EventDispatcher;
};
#endif /*__IMAGESCALEEVENT_H__*/