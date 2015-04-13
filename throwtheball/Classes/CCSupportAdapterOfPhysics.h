#ifndef CCSUPPORTADAPTEROFPHYSICAL_H
#define CCSUPPORTADAPTEROFPHYSICAL_H
#include "CCRoleAdapter.h"
#include "CCRole.h"
class CCSupportAdapterOfPhysics :
    public CCSupportAdapter, public cocos2d::Ref
{
protected:
    CCSupportAdapterOfPhysics(void);
    ~CCSupportAdapterOfPhysics(void);
public:
    CREATE_FUNC(CCSupportAdapterOfPhysics);
    virtual bool init();
    virtual cocos2d::Sprite* getSprite() override;
    virtual int getPropertyOfLive() override;
    virtual int getPropertyOfScore() override;
    virtual void setSupport(CCSupport* support);
    virtual RoleType getType() override;
protected:
    CCSupport* _support;
    friend class SuperRole;
};
#endif /*CCSUPPORTADAPTEROFPHYSICAL_H*/
