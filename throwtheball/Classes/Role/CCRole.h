#ifndef __ROLE_SPRITE_H__
#define __ROLE_SPRITE_H__

#include "Define.h"

class CCRoleFactory;

class SuperRole
{                       
protected:
    SuperRole():
        _roleType(Default),
        _live(0),
        _score(0)
    {}
    SuperRole(RoleType eRoleType, unsigned int iLive, unsigned int iScore):
        _roleType(eRoleType),
        _live(iLive),
        _score(iScore)
    {}

public:
    virtual ~SuperRole(){}
    virtual bool init();
protected:
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact) = 0;
    /*static bool onContactBegin(cocos2d::PhysicsContact& contact);*/

    //角色类型
    CC_ATTRIBUTE(RoleType, _roleType, Type);
    //角色生命
    CC_ATTRIBUTE(int, _live, Live);
    //当前角色分数
    CC_ATTRIBUTE(int, _score, Score);
};
#endif // __ROLE_SPRITE_H__