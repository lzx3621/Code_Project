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
    int getLive() const { return _live; }
    void setLive(const int &val) { _live = val; }
    int getScore() const { return _score; }
    void setScore(const int &val) { _score = val; }
protected:
    //��ȡ��Ϸ��Ҫ��ɫ�����SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
    static bool onContactBegin(cocos2d::PhysicsContact& contact);
public:
    //��ɫ����
    RoleType                _roleType;
    //��ɫ������һ������Ϊ������۳�������������Ϊ��
    int                     _live;
    //��ǰ��ɫ����
    int                     _score;

    //friend class CChero;
};

//������Ӧ��Ϊ��һ����Ϸģʽ��Ӧ��Ϊ��������

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


//������
class CCHydrangea : protected CCSupport
{
protected:
    CCHydrangea():CCSupport(DAMAGE_HYDRANGEA, 0, 200){}
    ~CCHydrangea(){}
    CREATE_FUNC(CCHydrangea);
public:
    bool init() override;
    friend class CCRoleFactory;
};

//��Ƭ��
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

//��������
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

//��������
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

//����Ҷ��
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

//������
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

//������
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

//������
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

//������
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