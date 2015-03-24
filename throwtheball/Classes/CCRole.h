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
    virtual ~SuperRole(){}

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    static SuperRole roleFactory(const RoleType& type);

protected:
    //��ȡ��Ϸ��Ҫ��ɫ�����SpriteFrame
    cocos2d::SpriteFrame*   getSpriteFrameByRoleType();
    //��ɫ����
    RoleType                _roleType;
    //��ɫ������һ������Ϊ������۳�������������Ϊ��
    int                     _live;
    //��ǰ��ɫ����
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