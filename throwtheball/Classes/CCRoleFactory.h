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
    //ʩ���йܣ������ľ�������������Parents����,���ؾ��������
    /*SuperRole*?�����С�����*/cocos2d::Sprite* createRoleForObject(RoleType Type, cocos2d::Node* const &Mount );
};

#endif // __ROLE_FACTORY_H__