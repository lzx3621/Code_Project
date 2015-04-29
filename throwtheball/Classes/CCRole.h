#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "Define.h"

class CCRoleFactory;
class CCHeroAdapterOfPhysics;

class SuperRole : public cocos2d::Sprite
{                       
protected:
    SuperRole():
        _roleType(Default),
        _live(0),
        _score(0)
    {}
    SuperRole(RoleType eRoleType, unsigned int iLive, unsigned int iScore):
        _roleType(eRoleType),
        _live(iLive),
        _score(iScore)
    {}

public:
    virtual ~SuperRole(){}
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
protected:
    //获取游戏主要角色精灵的SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
    static bool onContactBegin(cocos2d::PhysicsContact& contact);

    //角色类型
    CC_SYNTHESIZE(RoleType, _roleType, Type);
    //角色生命
    CC_SYNTHESIZE(int, _live, Live);
    //当前角色分数
    CC_SYNTHESIZE(int, _score, Score);
};

//主角类应当为在一个游戏模式中应该为单例存在

class CCHero : protected SuperRole
{
protected:
    CCHero():
        SuperRole(MAIN_HERO, 5, 0),
        _originLive(SuperRole::_live),
        _originScore(SuperRole::_score){}
    ~CCHero(){}
    CREATE_FUNC(CCHero);
public:
    bool init() override;
    const int getOriginLive() const { return _originLive; }
    const int getOriginScore() const { return _originScore; }
protected:
    //
    const int               _originLive;
    const int               _originScore;
    friend class CCRoleFactory;
    friend class CCHeroAdapterOfPhysics;
};

class CCSupport :public SuperRole
{
protected:
    CCSupport(RoleType eRoleType, int iLive, int iScore)
        :SuperRole(eRoleType, iLive, iScore){}
    ~CCSupport(){}
public:
    bool init() override;
};


//绣球类
class CCHydrangea : protected CCSupport
{
protected:
    CCHydrangea():CCSupport(GAIN_HYDRANGEA, 0, 200){}
    ~CCHydrangea(){}
    CREATE_FUNC(CCHydrangea);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//瓦片类
class CCTile : protected CCSupport
{
protected:
    CCTile():CCSupport(DAMAGE_TILE, -1, 0){}
    ~CCTile(){}
    CREATE_FUNC(CCTile);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//臭鸡蛋类
class CCBadGgg : protected CCSupport
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
class CCSmellyStockings : protected CCSupport
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
class CCBadVegetable : protected CCSupport
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
class CCSachet : protected CCSupport
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
class CCHandkerchief : protected CCSupport
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
class CCJadePendant : protected CCSupport
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
class CCJade : protected CCSupport
{
protected:
    CCJade():CCSupport(GAIN_JADE, 0, 200){}
    ~CCJade(){}
    CREATE_FUNC(CCJade);
public:
    bool init() override;
    friend class CCRoleFactory;
};

#endif // __ROLE_SPRITE_H__