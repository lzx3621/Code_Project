#ifndef __ROLE_FACTORY_H__
#define __ROLE_FACTORY_H__
#include "CCRole.h"

class CCRoleFactory_Interface
{
protected:
    CCRoleFactory_Interface();
    virtual ~CCRoleFactory_Interface();
    
public:
    cocos2d::Sprite* createRole(RoleType &Type, cocos2d::Node* const &Mount);
};

class CCRoleFactory
{
protected:
    CCRoleFactory();
    ~CCRoleFactory();
public:
    //ʩ���йܣ������ľ�������������Parents����,���ؾ��������
    /*SuperRole*?�����С�����*/cocos2d::Sprite* createRoleForObject(RoleType &Type, cocos2d::Node* const &Mount );
};

#endif // __ROLE_FACTORY_H__