#ifndef __ROLE_FACTORY_H__
#define __ROLE_FACTORY_H__

class CCRoleFactory
{
protected:
    CCRoleFactory();
    ~CCRoleFactory();
public:
    //ʩ���йܣ������ľ�������������Parents����,���ؾ��������
    static SuperRole* createRole(RoleType &Type, cocos2d::Node* const &Parents );
};

#endif // __ROLE_FACTORY_H__