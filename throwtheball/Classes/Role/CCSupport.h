#ifndef __CCSUPPORT_SPRITE_H__
#define __CCSUPPORT_SPRITE_H__
#include "CCRole.h"


class CCSupport :public SuperRole, public cocos2d::Sprite
{
protected:
    CCSupport(RoleType eRoleType, int iLive, int iScore)
        :SuperRole(eRoleType, iLive, iScore),
        _vectTemp(cocos2d::Vect::ZERO){}
    ~CCSupport(){}
public:
    bool init() override;
    virtual void pause(void) override;
    virtual void resume(void) override;
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
protected:
    cocos2d::SpriteFrame* getSpriteFrameByRoleType();
    cocos2d::Vect _vectTemp;
};

//瓦片类
class CCTile : public CCSupport
{
protected:
    CCTile():CCSupport(DAMAGE_TILE, -1, -200){}
    ~CCTile(){}
    CREATE_FUNC(CCTile);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//臭鸡蛋类
class CCBadGgg : public CCSupport
{
protected:
    CCBadGgg():CCSupport(DAMAGE_BAD_EGG, 0, -150){}
    ~CCBadGgg(){}
    CREATE_FUNC(CCBadGgg);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//臭袜子类
class CCSmellyStockings : public CCSupport
{
protected:
    CCSmellyStockings():CCSupport(DAMAGE_SMELLY_STOCKINGS, 0, -100){}
    ~CCSmellyStockings(){}
    CREATE_FUNC(CCSmellyStockings);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//栏菜叶类
class CCBadVegetable : public CCSupport
{
protected:
    CCBadVegetable():CCSupport(DAMAGE_BAD_VEGETABLE, 0, -50){}
    ~CCBadVegetable(){}
    CREATE_FUNC(CCBadVegetable);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//香囊类
class CCSachet : public CCSupport
{
protected:
    CCSachet():CCSupport(GAIN_SACHET, 0, 50){}
    ~CCSachet(){}
    CREATE_FUNC(CCSachet);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//手帕类
class CCHandkerchief : public CCSupport
{
protected:
    CCHandkerchief():CCSupport(GAIN_HANDKERCHIEF, 0, 100){}
    ~CCHandkerchief(){}
    CREATE_FUNC(CCHandkerchief);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//玉佩类
class CCJadePendant : public CCSupport
{
protected:
    CCJadePendant():CCSupport(GAIN_JADE_PENDANT, 0, 150){}
    ~CCJadePendant(){}
    CREATE_FUNC(CCJadePendant);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//如意类
class CCJade : public CCSupport
{
protected:
    CCJade():CCSupport(GAIN_JADE, 0, 200){}
    ~CCJade(){}
    CREATE_FUNC(CCJade);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//时钟类
class CCClock : public CCSupport
{
protected:
    CCClock():CCSupport(GAIN_CLOCK, 0, 0){}
    ~CCClock(){}
    CREATE_FUNC(CCClock);
public:
    bool init() override;
    friend class CCRoleFactory;
};

#endif // __CCSUPPORT_SPRITE_H__