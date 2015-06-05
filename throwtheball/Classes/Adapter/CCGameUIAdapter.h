#ifndef __GAMEUIADAPTER_H__
#define __GAMEUIADAPTER_H__
#include "cocos2d.h"
class CCGameUIAdapter
{
public:
    CCGameUIAdapter(void){}
    ~CCGameUIAdapter(void){}
    virtual void addRole(cocos2d::Node* Role) = 0;
    virtual void removeAllRole() = 0;
    virtual cocos2d::Vector<cocos2d::Node*>& getRole() = 0;
    virtual void updateHeroScoreAndLive(const int& Hero, const int& score) = 0;
    virtual void updateTime(const int& time) = 0;
    virtual void showPauseUI() = 0;
    virtual void hidePauseUI() = 0;
    virtual void showHaze() = 0;
    virtual void hideHaze() = 0;
    virtual void showToast() = 0;
    virtual void hideToast() = 0;
    virtual void setlimited(bool set) = 0;
    virtual void showGameOverUI(const int &score) = 0;
    virtual void hideGameOverUI() = 0;
    virtual cocos2d::Scene* getGameScene() = 0;
};


#endif /*__GAMEUIADAPTER_H__*/