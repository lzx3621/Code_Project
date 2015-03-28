#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"
class CCNormalRule :
    public CCRule
{
public:
    CCNormalRule(void);
    ~CCNormalRule(void);
    
public:
    virtual void onHeroContact(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore) override;
    virtual void onStart() override;
    virtual void onPause() override;
    virtual void onEnd() override;

};

#endif __NORMALRULE_H__