#ifndef __ROLE_FACTORY_H__
#define __ROLE_FACTORY_H__
#include "CCRole.h"

class CCRoleFactory_Interface
{
protected:
    CCRoleFactory_Interface();
    
public:
    virtual ~CCRoleFactory_Interface();
    virtual cocos2d::Sprite* createRole(RoleType Type, cocos2d::Node* const &Mount) = 0;
};

class CCRoleFactoryOfObject: public CCRoleFactory_Interface
{
protected:
    CCRoleFactoryOfObject();
    ~CCRoleFactoryOfObject();
public:
    //施行托管，创建的精灵生命周期由Parents控制,返回精灵的引用
    /*SuperRole*?考虑中。。。*/cocos2d::Sprite* createRoleForObject(RoleType Type, cocos2d::Node* const &Mount );
};

#endif // __ROLE_FACTORY_H__