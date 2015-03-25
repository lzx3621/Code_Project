#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "cocos2d.h"

enum RoleType
{
    Default = -1,
    MAIN_HERO,                  //主角
    DAMAGE_HYDRANGEA,           //绣球
    DAMAGE_TILE,                //瓦片
    DAMAGE_BAD_EGG,             //臭鸡蛋
    DAMAGE_SMELLY_STOCKINGS,    //臭袜子
    DAMAGE_BAD_VEGETABLE,       //栏菜叶
    GAIN_SACHET,                //香囊
    GAIN_HANDKERCHIEF,          //手帕
    GAIN_JADE_PENDANT,          //玉佩
    GAIN_JADE                   //如意
};  
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
    virtual ~SuperRole(){}

public:
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

class CCRoleFactory
{
protected:
    CCRoleFactory();
    ~CCRoleFactory();
public:
    //施行托管，创建的精灵生命周期由Parents控制,返回精灵的引用
    static SuperRole* createRole(RoleType &Type, cocos2d::Node* const &Parents );
};


//主角类应当为在一个游戏模式中应该为单例存在

class CChero : public SuperRole
{
/*
    struct IUpdateLiveAndScore 
    {
    protected:
        IUpdateLiveAndScore(){}
        ~IUpdateLiveAndScore(){}
    public:
        virtual void onUpdateLiveAndScore() = 0;
    };*/
    typedef std::function<void(const int& iHerolive, const int& iHeroScore)> UpdateLiveAndScore;
protected:
    CChero():SuperRole(MAIN_HERO, 5, 0){}
    ~CChero(){}
    CREATE_FUNC(CChero);
public:
    bool init() override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void setUpdateLiveAndScoreCallback( UpdateLiveAndScore& onUpdateLiveAndScore) { _onUpdateLiveAndScore = onUpdateLiveAndScore;}
    UpdateLiveAndScore getUpdateLiveAndScoreCallback() const {return _onUpdateLiveAndScore;}
protected:
/*    IUpdateLiveAndScore _onUpdateLiveAndScore;*/
    //数据更新，用于通知界面更新数据
    UpdateLiveAndScore _onUpdateLiveAndScore;
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

//绣球类
class CCTile : public SuperRole
{
protected:
    CCTile():SuperRole(DAMAGE_HYDRANGEA, 0, 200){}
    ~CCTile(){}
    CREATE_FUNC(CCTile);
public:
    bool init() override;
    friend CCRoleFactory;
};

#endif // __HELLOWORLD_SCENE_H__