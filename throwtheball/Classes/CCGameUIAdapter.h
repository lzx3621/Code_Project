#ifndef __GAMEUIADAPTER_H__
#define __GAMEUIADAPTER_H__
#include "cocos2d.h"
class CCGameUIAdapter
{
public:
    CCGameUIAdapter(void);
    ~CCGameUIAdapter(void);
    virtual void addRole(cocos2d::Node* Role) = 0;
    virtual void updateheroScoreAndLive(int Hero, int score) = 0;
    virtual cocos2d::Scene* getGameScene() = 0;
};


#endif /*__GAMEUIADAPTER_H__*/