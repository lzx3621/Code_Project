#ifndef __ROLEADAPTER_H__
#define __ROLEADAPTER_H__
#include "cocos2d.h"
class CCRoleAdapter
{
public:
    CCRoleAdapter(void);
    ~CCRoleAdapter(void);
    virtual cocos2d::Sprite* getSprite() = 0;
    virtual cocos2d::Value getOrigin(cocos2d::Value) = 0;
    virtual cocos2d::Value getValueBykey(cocos2d::Value) = 0;
};
#endif __ROLEADAPTER_H__
