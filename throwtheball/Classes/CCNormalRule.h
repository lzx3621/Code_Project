#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"

class CCHeroAdapter;
class CCSupportAdapter;

typedef std::function<void(int, int)> onHeroUpdate;
class CCNormalRule :
    public CCRule
{
protected:
    CCNormalRule(void):_isStart(false){}
    CCNormalRule(CCHeroAdapter* heroSprite,
            CCRoleFactory* roleFactory)
            :CCRule(heroSprite, roleFactory){}
public:
    CREATE_FUNC(CCNormalRule);
    ~CCNormalRule(void){}
    virtual bool init() override;
    virtual void onStart() override;
    virtual void onRestat() override;
    virtual void onPause() override;
    virtual void onEnd() override;
    void createObjectOffFall(float dt);
    virtual bool onHeroTouchBegan(cocos2d::Touch*, cocos2d::Event*) ;
	virtual void onHeroTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) ;
    virtual void onHeroContact(CCHeroAdapter* hero, CCSupportAdapter* support);
    virtual void onObjectContactBottom(CCSupportAdapter* support);
protected:
	cocos2d::Scene* _gamescene;
	bool			_isStart;
};

#endif __NORMALRULE_H__