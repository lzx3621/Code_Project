#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"
#include "CCRoleFactory.h"
#include "CCRoleAdapter.h"
/************************************************************************/
/* �������ʹ�ã�������Ϸ��ν���                                       */
/************************************************************************/
class CCRule:public cocos2d::Node
{
protected:
    CCRule(void): _heroSprite(nullptr), _roleFactory(nullptr){}
    CCRule(CCRoleAdapter* heroSprite,
        CCRoleFactory* roleFactory)
        :_heroSprite(heroSprite),
        _roleFactory(roleFactory){}
    ~CCRule(void){}
public:
    virtual bool init()
    { 
        if (cocos2d::Node::init())
        {
            setName("Rule"); 
            return true;
        }
        else
        {
            return false;
        }
        
    }
    virtual void onHeroContact(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore)=0;
    virtual void onStart() = 0;
    virtual void onRestat() = 0;
    virtual void onPause() = 0;
    virtual void onEnd() = 0;

protected:
    CCRoleAdapter*          _heroSprite;
    ptr_RoleFactory         _roleFactory;
};

#endif __RULE_FACTORY_H__


