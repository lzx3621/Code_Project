#ifndef __ROLEADAPTER_H__
#define __ROLEADAPTER_H__
#include "cocos2d.h"
#include "Define.h"
class CCSupportAdapter;
class CCHeroAdapter;
typedef std::function<void(CCHeroAdapter*, CCSupportAdapter*)> onHeroContact;
typedef std::function<void(CCSupportAdapter*)> onObjectContactBottom;

class CCHeroAdapter 
{
public:
    CCHeroAdapter(void){}
    ~CCHeroAdapter(void){}
    virtual bool init()= 0;
    virtual cocos2d::Sprite* getSprite() = 0;
    virtual int getOriginLive() = 0;
    virtual int getOriginScore() = 0;
    virtual int getCurrentScore() = 0;
    virtual void setCurrentScore(const unsigned int & val) = 0;
    virtual int getCurrentLive() = 0;
    virtual void setCurrentLive(const unsigned int & val) = 0;
    static void setHeroContactCallback(onHeroContact HeroContact);
protected:
    static onHeroContact s_onHeroContact;
};


class CCSupportAdapter
{
public:
    CCSupportAdapter(void){}
    ~CCSupportAdapter(void){}
    virtual bool init()= 0;
    virtual cocos2d::Sprite* getSprite() = 0;
    virtual int getPropertyOfLive() = 0;
    virtual int getPropertyOfScore() = 0;
    static void setObjectContactBottomCallback(onObjectContactBottom ObjectContactBottom);
    virtual RoleType getType() = 0;
protected:
    static onObjectContactBottom s_onObjectContactBottom;
};

#endif /*__ROLEADAPTER_H__*/
