#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "cocos2d.h"

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

class CCRoleFactory
{
protected:
    CCRoleFactory();
    ~CCRoleFactory();
public:
    //ʩ���йܣ������ľ�������������Parents����,���ؾ��������
    static SuperRole* createRole(RoleType &Type, cocos2d::Node* const &Parents );
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

//������
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