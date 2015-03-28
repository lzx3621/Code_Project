#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"
#include "CCRoleFactory.h"
#include "CCRoleAdapter.h"
/************************************************************************/
/* 定义规则使用，决定游戏如何进行                                       */
/************************************************************************/
class CCRule
{
protected:
    CCRule(void);
    ~CCRule(void);
public:
    virtual void onHeroContact(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore)=0;
    virtual void onStart() = 0;
    virtual void onPause() = 0;
    virtual void onEnd() = 0;

protected:
    cocos2d::Scene*             _gameScene;
    CCRoleAdapter*              _heroSprite;
    CCRoleFactory_Interface*    _roleFactory;
};

#endif __RULE_FACTORY_H__


