#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "cocos2d.h"

class CCRoleFactory;

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
    //���ݸ��£�����֪ͨ�����������
    UpdateLiveAndScore _onUpdateLiveAndScore;
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
    CCTile():SuperRole(DAMAGE_TILE, 0, 200){}
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
    CCBadGgg():SuperRole(DAMAGE_BAD_EGG, 0, 200){}
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
    CCSmellyStockings():SuperRole(DAMAGE_SMELLY_STOCKINGS, 0, 200){}
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
    CCBadVegetable():SuperRole(DAMAGE_BAD_VEGETABLE, 0, 200){}
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
    CCSachet():SuperRole(GAIN_SACHET, 0, 200){}
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
    CCHandkerchief():SuperRole(GAIN_HANDKERCHIEF, 0, 200){}
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
    CCJadePendant():SuperRole(GAIN_JADE_PENDANT, 0, 200){}
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