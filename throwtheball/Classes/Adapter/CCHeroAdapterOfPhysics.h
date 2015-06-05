#ifndef CHEROADAPTEROFPHYSICAL_H
#define CHEROADAPTEROFPHYSICAL_H
#include "CCRoleAdapter.h"

class CCHero;
class CCHeroAdapterOfPhysics :
    public CCHeroAdapter/*, public cocos2d::Ref*/
{
protected:
    CCHeroAdapterOfPhysics(CCHero* hero);
    ~CCHeroAdapterOfPhysics(void);
public:
    virtual bool init();
    virtual cocos2d::Sprite* getHero() override;
    virtual void setCurrentScore(const unsigned int & val) override;
    virtual int getCurrentScore() override;
    virtual int getCurrentLive() override;
    virtual void setCurrentLive(const unsigned int & val) override;
    static CCHeroAdapterOfPhysics* create(CCHero* hero);
    
protected:
    CCHero* _hero;
    friend class CCHero;
};
#endif /*CHEROADAPTEROFPHYSICAL_H*/
