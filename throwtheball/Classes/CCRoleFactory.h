#ifndef __ROLE_FACTORY_H__
#define __ROLE_FACTORY_H__
#include "CCRole.h"
#include "CCRoleAdapter.h"

class CCRoleFactory;

typedef std::shared_ptr<CCRoleFactory> ptr_RoleFactory;

class CCRoleFactory/*:public cocos2d::Ref*/
{
protected:
    CCRoleFactory():_parents(nullptr){}
    CCRoleFactory(cocos2d::Node* parents):_parents(parents){}
public:
    virtual ~CCRoleFactory(){}
    virtual bool init() = 0;
    virtual cocos2d::Sprite* createRole(RoleType Type, const cocos2d::Vec2 &pos) = 0;
    virtual CCRoleAdapter* getRoleAdapter(cocos2d::Sprite* factoryCreate) = 0;
protected:
    cocos2d::Node* _parents;
};

#endif // __ROLE_FACTORY_H__