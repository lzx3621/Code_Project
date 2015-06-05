#ifndef CCSUPPORTADAPTEROFPHYSICAL_H
#define CCSUPPORTADAPTEROFPHYSICAL_H
#include "CCRoleAdapter.h"
class CCSupport;
class CCSupportAdapterOfPhysics :
    public CCSupportAdapter, public cocos2d::Ref
{
protected:
    CCSupportAdapterOfPhysics(CCSupport* support);
    virtual ~CCSupportAdapterOfPhysics(void);
public:
    static CCSupportAdapterOfPhysics* create(CCSupport* support);
    virtual bool init();
    virtual cocos2d::Sprite* getSprite() override;
    virtual int getPropertyOfLive() override;
    virtual int getPropertyOfScore() override;
    virtual void setSupport(CCSupport* support);
    virtual RoleType getType() override;
protected:
    CCSupport* _support;
    friend class CCSupport;
};
#endif /*CCSUPPORTADAPTEROFPHYSICAL_H*/
