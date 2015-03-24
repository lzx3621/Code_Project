#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "cocos2d.h"

class SuperRole : public cocos2d::Sprite
{
public:
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
protected:
    SuperRole():
        _roleType(Default),
        _live(0),
        _score(0)
    {}
    virtual ~SuperRole(){}

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    static SuperRole roleFactory(const RoleType& type);

protected:
    //获取游戏主要角色精灵的SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
    //角色类型
    RoleType                _roleType;
    //角色生命，一般主角为正，会扣除主角生命数的为负
    int                     _live;
    //当前角色分数
    int                     _score;

};

class CChero : public SuperRole
{
protected:
    CChero():SuperRole(){}
    ~CChero(){}
protected:

};

#endif // __HELLOWORLD_SCENE_H__