#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"
#include "CCRoleFactory.h"
#include "CCRoleAdapter.h"
/************************************************************************/
/* 定义规则使用，决定游戏如何进行                                       */
/************************************************************************/
class CCRule:public cocos2d::Node
{
protected:
    CCRule(void): _hero(nullptr), _roleFactory(nullptr){}
    CCRule(CCHeroAdapter* heroSprite,
        CCRoleFactory* roleFactory)
        :_hero(_hero),
        _roleFactory(roleFactory){}
    ~CCRule(void){}
public:
    virtual bool init()
    { 
        if (cocos2d::Node::init())
        {
            setName("Rule"); 
            return true;
        }
        else
        {
            return false;
        }
        
    }
    virtual void onStart() = 0;
    virtual void onRestat() = 0;
    virtual void onPause() = 0;
    virtual void onEnd() = 0;
    //virtual bool onHeroTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) = 0;
protected:
    CCHeroAdapter*          _hero;
    CCRoleFactory*          _roleFactory;
};

#endif __RULE_FACTORY_H__


