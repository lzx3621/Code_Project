#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"
class CCNormalRule :
    public CCRule
{
protected:
    CCNormalRule(void);
    CCNormalRule(CCRoleAdapter* heroSprite,
            CCRoleFactory* roleFactory)
            :CCRule(heroSprite, roleFactory){}
    //CREATE_FUNC(CCNormalRule);
public:
    static CCNormalRule* create(cocos2d::Node* const parent);
    ~CCNormalRule(void);
    virtual bool init() override;
    virtual void onStart() override;
    virtual void onRestat() override;
    virtual void onPause() override;
    virtual void onEnd() override;
    void createObjectOffFall(float dt);
    virtual void onHeroContact(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore) override;
};

#endif __NORMALRULE_H__