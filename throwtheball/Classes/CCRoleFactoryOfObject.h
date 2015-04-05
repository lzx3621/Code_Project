#ifndef __CCROLEFACTORYOFOBJECT_H__
#define __CCROLEFACTORYOFOBJECT_H__
#include "CCRole.h"
#include "CCRoleFactory.h"


class CCRoleFactoryOfObject: public CCRoleFactory
{

protected:
    CCRoleFactoryOfObject(){}
    CCRoleFactoryOfObject(cocos2d::Node* parents):CCRoleFactory(parents){}
public:
    ~CCRoleFactoryOfObject(){}
    static ptr_RoleFactory create(cocos2d::Node* const &parents);
    virtual bool init() override;
    //施行托管，创建的精灵生命周期由Parents控制,返回精灵的引用
    cocos2d::Sprite* createRole(RoleType Type, const cocos2d::Vec2 &pos) override{ return createRoleForObject(Type, pos);}
    virtual CCRoleAdapter* getRoleAdapter(cocos2d::Sprite* factoryCreate) override;
protected:
    SuperRole* createRoleForObject(RoleType Type, const cocos2d::Vec2 &pos );
};

#endif // __CCROLEFACTORYOFOBJECT_H__