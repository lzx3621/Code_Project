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
    //��ȡ��Ϸ��Ҫ��ɫ�����SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
public:
    //��ɫ����
    RoleType                _roleType;
    //��ɫ������һ������Ϊ������۳�������������Ϊ��
    int                     _currentLive;
    //��ǰ��ɫ����
    int                     _currentScore;
    //
    const int               _originLive;
    const int               _originScore;
    //friend class CChero;
};

//������Ӧ��Ϊ��һ����Ϸģʽ��Ӧ��Ϊ��������

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
    //���ݸ��£�����֪ͨ�����������
    HeroContact _onHeroContact;
    friend class CCRoleFactoryOfObject;
};


//������
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

//��Ƭ��
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

//��������
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

//��������
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

//����Ҷ��
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

//������
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

//������
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

//������
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

//������
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