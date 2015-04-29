#ifndef CHEROADAPTEROFPHYSICAL_H
#define CHEROADAPTEROFPHYSICAL_H
#include "CCRoleAdapter.h"
#include "CCRole.h"
class CCHeroAdapterOfPhysics :
    public CCHeroAdapter, public cocos2d::Ref
{
protected:
    CCHeroAdapterOfPhysics(void);
    ~CCHeroAdapterOfPhysics(void);
public:
    virtual bool init();
    virtual cocos2d::Sprite* getSprite() override;
    virtual void setHero(CCHero* hero);
    virtual int getOriginLive() override;
    virtual int getOriginScore() override;
    virtual void setCurrentScore(const unsigned int & val) override;
    virtual int getCurrentScore() override;
    virtual int getCurrentLive() override;
    virtual void setCurrentLive(const unsigned int & val) override;
    CREATE_FUNC(CCHeroAdapterOfPhysics);
protected:
    CCHero* _hero;
    friend class SuperRole;
};
#endif /*CHEROADAPTEROFPHYSICAL_H*/
