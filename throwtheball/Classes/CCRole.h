#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "Define.h"

class CCRoleFactoryOfObject;
class CChero;

class SuperRole : public cocos2d::Sprite
{                       
protected:
    SuperRole():
        _roleType(Default),
        _currentLive(0),
        _currentScore(0),
        _originLive(0),
        _originScore(0)
    {}
    SuperRole(RoleType eRoleType, int iLive, int iScore):
        _roleType(eRoleType),
        _currentLive(iLive),
        _currentScore(iScore),
        _originLive(iLive),
        _originScore(iScore)
    {}

public:
    virtual ~SuperRole(){}
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    RoleType getType(){ return _roleType; }
    int getCurrentLive() {return _currentLive;}
    int getCurrentScore() {return _currentScore;}
protected:
    //获取游戏主要角色精灵的SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
public:
    //角色类型
    RoleType                _roleType;
    //角色生命，一般主角为正，会扣除主角生命数的为负
    int                     _currentLive;
    //当前角色分数
    int                     _currentScore;
    //
    const int               _originLive;
    const int               _originScore;
    //friend class CChero;
};

//主角类应当为在一个游戏模式中应该为单例存在

class CChero : protected SuperRole
{
/*
    struct IHeroContact 
    {
    protected:
        IHeroContact(){}
        ~IHeroContact(){}
    public:
        virtual void onHeroContact() = 0;
    };*/
protected:
    CChero():SuperRole(MAIN_HERO, 5, 0){}
    ~CChero(){}
    CREATE_FUNC(CChero);
public:
    bool init() override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void setHeroContactCallback( HeroContact& onHeroContact) { _onHeroContact = onHeroContact;}
    HeroContact getHeroContactCallback() const {return _onHeroContact;}
protected:
/*    IHeroContact _onHeroContact;*/
    //数据更新，用于通知界面更新数据
    HeroContact _onHeroContact;
    friend class CCRoleFactoryOfObject;
};


//绣球类
class CCHydrangea : protected SuperRole
{
protected:
    CCHydrangea():SuperRole(DAMAGE_HYDRANGEA, 0, 200){}
    ~CCHydrangea(){}
    CREATE_FUNC(CCHydrangea);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//瓦片类
class CCTile : protected SuperRole
{
protected:
    CCTile():SuperRole(DAMAGE_TILE, -1, 0){}
    ~CCTile(){}
    CREATE_FUNC(CCTile);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//臭鸡蛋类
class CCBadGgg : protected SuperRole
{
protected:
    CCBadGgg():SuperRole(DAMAGE_BAD_EGG, 0, -150){}
    ~CCBadGgg(){}
    CREATE_FUNC(CCBadGgg);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//臭袜子类
class CCSmellyStockings : protected SuperRole
{
protected:
    CCSmellyStockings():SuperRole(DAMAGE_SMELLY_STOCKINGS, 0, -100){}
    ~CCSmellyStockings(){}
    CREATE_FUNC(CCSmellyStockings);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//栏菜叶类
class CCBadVegetable : protected SuperRole
{
protected:
    CCBadVegetable():SuperRole(DAMAGE_BAD_VEGETABLE, 0, -50){}
    ~CCBadVegetable(){}
    CREATE_FUNC(CCBadVegetable);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//香囊类
class CCSachet : protected SuperRole
{
protected:
    CCSachet():SuperRole(GAIN_SACHET, 0, 50){}
    ~CCSachet(){}
    CREATE_FUNC(CCSachet);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//手帕类
class CCHandkerchief : protected SuperRole
{
protected:
    CCHandkerchief():SuperRole(GAIN_HANDKERCHIEF, 0, 100){}
    ~CCHandkerchief(){}
    CREATE_FUNC(CCHandkerchief);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//玉佩类
class CCJadePendant : protected SuperRole
{
protected:
    CCJadePendant():SuperRole(GAIN_JADE_PENDANT, 0, 150){}
    ~CCJadePendant(){}
    CREATE_FUNC(CCJadePendant);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

//如意类
class CCJade : protected SuperRole
{
protected:
    CCJade():SuperRole(GAIN_JADE, 0, 200){}
    ~CCJade(){}
    CREATE_FUNC(CCJade);
public:
    bool init() override;
    friend class CCRoleFactoryOfObject;
};

#endif // __ROLE_SPRITE_H__