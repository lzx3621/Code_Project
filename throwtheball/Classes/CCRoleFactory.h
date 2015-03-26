#ifndef __ROLE_FACTORY_H__
#define __ROLE_FACTORY_H__

class CCRoleFactory
{
protected:
    CCRoleFactory();
    ~CCRoleFactory();
public:
    //施行托管，创建的精灵生命周期由Parents控制,返回精灵的引用
    static SuperRole* createRole(RoleType &Type, cocos2d::Node* const &Parents );
};

#endif // __ROLE_FACTORY_H__