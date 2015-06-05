#ifndef __LIMITERULE_H__
#define __LIMITERULE_H__
#include "CCNormalRule.h"

class CCHeroAdapter;
class CCSupportAdapter;
class CCRoleFactory;
class CCGameUIAdapter;
enum RoleType :int;

class CCLimitedRule :public CCNormalRule
{
protected:
    CCLimitedRule();
    ~CCLimitedRule(void);
    virtual bool init(CCGameUIAdapter* UIAdapter);
public:
    virtual void gameStart() override;
    virtual void gameRestart() override;
    static CCNormalRule* create(CCGameUIAdapter* UIAdapter);
    virtual bool useObject(const std::string& Object);
protected:
    virtual void createObjectOffFall(float dt);
    virtual void onHeroContact(CCHeroAdapter& hero, CCSupportAdapter& support);
    virtual bool isGameContinue(CCHeroAdapter &hero, CCSupportAdapter &support);
    void countDown(float d);
    volatile int _time;
};

#endif /*__LIMITERULE_H__*/