#ifndef __SPRITEBUTTOM_H__
#define __SPRITEBUTTOM_H__
#include "cocos2d.h"
#include "base\CCEventDispatcher.h"

class CCSpriteButtom : public cocos2d::Node
{
public:
    CCSpriteButtom();
    ~CCSpriteButtom();

    virtual bool init();
    CREATE_FUNC(CCSpriteButtom);
    static CCSpriteButtom* create(const char* backgroundImage,cocos2d::Size dialogSize);

    //touch事件监听 屏蔽向下触摸
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event);
    
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    cocos2d::Sprite* _Sprite;
   
};

#endif __SPRITEBUTTOM_H__