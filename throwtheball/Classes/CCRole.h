#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "cocos2d.h"

class SuperRole : public cocos2d::Sprite
{
public:
	enum RoleType
	{
        Default = -1,
		MAIN_HERO,                  //����
        DAMAGE_HYDRANGEA,           //����
        DAMAGE_TILE,                //��Ƭ
        DAMAGE_BAD_EGG,             //������
        DAMAGE_SMELLY_STOCKINGS,    //������
        DAMAGE_BAD_VEGETABLE,       //����Ҷ
        GAIN_SACHET,                //����
        GAIN_HANDKERCHIEF,          //����
        GAIN_JADE_PENDANT,          //����
        GAIN_JADE                   //����
	};                                
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
    //��ȡ��Ϸ��Ҫ��ɫ�����SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
public:
    //��ɫ����
    RoleType                _roleType;
    //��ɫ������һ������Ϊ������۳�������������Ϊ��
    int                     _live;
    //��ǰ��ɫ����
    int                     _score;

};


//������Ӧ��Ϊ��������

class CChero : public SuperRole
{
/*
    struct IheroDeath 
    {
    protected:
        IheroDeath(){}
        ~IheroDeath(){}
    public:
        virtual void onheroDeath() = 0;
    };*/
protected:
    CChero():SuperRole(MAIN_HERO, 5, 0){}
    ~CChero(){}
public:
    bool init() override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void setHeroDeathCallback( const std::function<void()>& onHeroDeath) { _onHeroDeath = onHeroDeath;}
    const std::function<void()> getHeroDeathCallback() {return &_onHeroDeath;}
protected:
/*    IheroDeath _onheroDeath;*/
    std::function<void()> _onHeroDeath;
};


//������
class CCHydrangea : public SuperRole
{
protected:
    CCHydrangea():SuperRole(DAMAGE_HYDRANGEA, 0, 200){}
    ~CCHydrangea();
public:
    bool init() override;
};
#endif // __HELLOWORLD_SCENE_H__