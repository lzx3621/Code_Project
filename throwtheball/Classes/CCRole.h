#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "Define.h"

class CCRoleFactory;

class SuperRole : public cocos2d::Sprite
{                       
protected:
    SuperRole():
        _roleType(Default),
        _live(0),
        _score(0)
    {}
    SuperRole(RoleType eRoleType, int iLive, int iScore):
        _roleType(eRoleType),
        _live(iLive),
        _score(iScore)
    {}

public:
    virtual ~SuperRole(){}
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    RoleType getType(){ return _roleType; }

protected:
    //获取游戏主要角色精灵的SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
public:
    //角色类型
    RoleType                _roleType;
    //角色生命，一般主角为正，会扣除主角生命数的为负
    int                     _live;
    //当前角色分数
    int                     _score;

};

//主角类应当为在一个游戏模式中应该为单例存在

class CChero : public SuperRole
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
    CREATE_FUNC(CChero);
public:
    ~CChero(){}
    bool init() override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void setHeroContactCallback( HeroContact& onHeroContact) { _onHeroContact = onHeroContact;}
    HeroContact getHeroContactCallback() const {return _onHeroContact;}
protected:
/*    IHeroContact _onHeroContact;*/
    //数据更新，用于通知界面更新数据
    HeroContact _onHeroContact;
    friend CCRoleFactory;
};


//绣球类
class CCHydrangea : public SuperRole
{
protected:
    CCHydrangea():SuperRole(DAMAGE_HYDRANGEA, 0, 200){}
    ~CCHydrangea(){}
    CREATE_FUNC(CCHydrangea);
public:
    bool init() override;
    friend CCRoleFactory;
};

//瓦片类
class CCTile : public SuperRole
{
protected:
    CCTile():SuperRole(DAMAGE_TILE, -1, 0){}
    ~CCTile(){}
    CREATE_FUNC(CCTile);
public:
    bool init() override;
    friend CCRoleFactory;
};

//臭鸡蛋类
class CCBadGgg : public SuperRole
{
protected:
    CCBadGgg():SuperRole(DAMAGE_BAD_EGG, 0, -150){}
    ~CCBadGgg(){}
    CREATE_FUNC(CCBadGgg);
public:
    bool init() override;
    friend CCRoleFactory;
};

//臭袜子类
class CCSmellyStockings : public SuperRole
{
protected:
    CCSmellyStockings():SuperRole(DAMAGE_SMELLY_STOCKINGS, 0, -100){}
    ~CCSmellyStockings(){}
    CREATE_FUNC(CCSmellyStockings);
public:
    bool init() override;
    friend CCRoleFactory;
};

//栏菜叶类
class CCBadVegetable : public SuperRole
{
protected:
    CCBadVegetable():SuperRole(DAMAGE_BAD_VEGETABLE, 0, -50){}
    ~CCBadVegetable(){}
    CREATE_FUNC(CCBadVegetable);
public:
    bool init() override;
    friend CCRoleFactory;
};

//香囊类
class CCSachet : public SuperRole
{
protected:
    CCSachet():SuperRole(GAIN_SACHET, 0, 50){}
    ~CCSachet(){}
    CREATE_FUNC(CCSachet);
public:
    bool init() override;
    friend CCRoleFactory;
};

//手帕类
class CCHandkerchief : public SuperRole
{
protected:
    CCHandkerchief():SuperRole(GAIN_HANDKERCHIEF, 0, 100){}
    ~CCHandkerchief(){}
    CREATE_FUNC(CCHandkerchief);
public:
    bool init() override;
    friend CCRoleFactory;
};

//玉佩类
class CCJadePendant : public SuperRole
{
protected:
    CCJadePendant():SuperRole(GAIN_JADE_PENDANT, 0, 150){}
    ~CCJadePendant(){}
    CREATE_FUNC(CCJadePendant);
public:
    bool init() override;
    friend CCRoleFactory;
};

//如意类
class CCJade : public SuperRole
{
protected:
    CCJade():SuperRole(GAIN_JADE, 0, 200){}
    ~CCJade(){}
    CREATE_FUNC(CCJade);
public:
    bool init() override;
    friend CCRoleFactory;
};

#endif // __ROLE_SPRITE_H__