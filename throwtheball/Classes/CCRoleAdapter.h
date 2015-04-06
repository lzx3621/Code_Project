#ifndef __ROLEADAPTER_H__
#define __ROLEADAPTER_H__
#include "cocos2d.h"
class CCHeroAdapter;
class CCSupportAdapter;
typedef std::function<void(CCHeroAdapter*, CCSupportAdapter*)> fancHeroContact;
typedef std::function<void(cocos2d::Sprite*)> fancObjectContactBottom;
class CCRoleAdapter
{
public:
    CCRoleAdapter(void);
    ~CCRoleAdapter(void);
    virtual bool init()= 0;
    virtual cocos2d::Sprite* getSprite() = 0;
    virtual cocos2d::Value getValueByKey(cocos2d::Value) = 0;
    virtual bool setValueBykey(const cocos2d::Value& key, const cocos2d::Value& value) = 0;
    virtual RoleType getType() = 0;
};

class CCHeroAdapter 
{
public:
    CCHeroAdapter(void);
    ~CCHeroAdapter(void);
    virtual bool init()= 0;
    virtual cocos2d::Sprite* getSprite() = 0;
    virtual cocos2d::Value getOrigin(cocos2d::Value) = 0;
    virtual cocos2d::Value getValueBykey(cocos2d::Value) = 0;
    virtual void setHeroContactCallback(const fancHeroContact&) = 0;
    virtual void setObjectContactBottomCallback(const fancObjectContactBottom&) = 0;
    virtual RoleType getType() = 0;
};

class CCSupportAdapter
{
public:
    CCSupportAdapter(void);
    ~CCSupportAdapter(void);
    virtual bool init()= 0;
    virtual cocos2d::Sprite* getSprite() = 0;
protected:
    virtual cocos2d::Value getOrigin(cocos2d::Value) = 0;
    virtual cocos2d::Value getValueBykey(cocos2d::Value) = 0;
public:
    virtual void setObjectContactBottomCallback(const fancObjectContactBottom&) = 0;
    virtual RoleType getType() = 0;
};
#endif __ROLEADAPTER_H__
