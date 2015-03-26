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

//������Ӧ��Ϊ��һ����Ϸģʽ��Ӧ��Ϊ��������

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
    //���ݸ��£�����֪ͨ�����������
    HeroContact _onHeroContact;
    friend CCRoleFactory;
};


//������
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

//��Ƭ��
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

//��������
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

//��������
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

//����Ҷ��
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

//������
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

//������
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

//������
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

//������
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