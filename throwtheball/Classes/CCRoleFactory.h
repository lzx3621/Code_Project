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
    virtual bool init() override;
    //施行托管，创建的精灵生命周期由Parents控制,返回精灵的引用
    virtual cocos2d::Sprite* createRole(RoleType Type, const cocos2d::Vec2 &pos) ;
    virtual CCRoleAdapter* getRoleAdapter(cocos2d::Sprite* factoryCreate) ;
protected:
    SuperRole* createRoleOfPhysics(RoleType Type, const cocos2d::Vec2 &pos );
    cocos2d::PhysicsWorld* _physicsWorld;
    friend class CCRoleFactory;
};

#endif // __CCROLEFACTORYOFOBJECT_H__