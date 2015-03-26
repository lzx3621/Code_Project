#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"
/************************************************************************/
/* �������ʹ�ã�������Ϸ��ν���                                       */
/************************************************************************/
class CCRule
{
protected:
    CCRule(void);
    ~CCRule(void);
public:
    virtual void onHeroContact(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore)=0;
protected:
    cocos2d::Scene _gameScene;

};

#endif __RULE_FACTORY_H__


