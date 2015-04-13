#ifndef __CCROLEFACTORYOFOBJECT_H__
#define __CCROLEFACTORYOFOBJECT_H__
#include "CCRole.h"
#include "CCRoleAdapter.h"


class CCRoleFactory: public cocos2d::Node
{
protected:
    CCRoleFactory():_physicsWorld(nullptr){}
    ~CCRoleFactory(){}
public:
    CREATE_FUNC(CCRoleFactory);
    //virtual bool init() override;
    //ʩ���йܣ������ľ�������������Parents����,���ؾ��������
    virtual cocos2d::Sprite* createRole(RoleType Type, const cocos2d::Vec2 &pos = cocos2d::Vec2(0,0));
protected:
    SuperRole* createRoleOfPhysics(RoleType Type, const cocos2d::Vec2 &pos);
    cocos2d::PhysicsWorld* _physicsWorld;
    friend class CCRoleFactory;
};

#endif // __CCROLEFACTORYOFOBJECT_H__