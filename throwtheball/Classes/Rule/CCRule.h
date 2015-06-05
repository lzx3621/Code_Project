#ifndef __RULE_H__
#define __RULE_H__

#include "cocos2d.h"

/************************************************************************/
/* 定义规则使用，决定游戏如何进行                                       */
/************************************************************************/
class CCRule /*:public cocos2d::Node*/
{
protected:
    CCRule(void){}
    ~CCRule(void){}
public:
    virtual void gameStart() = 0;
    virtual void gameRestart() = 0;
    virtual void gamePause() = 0;
    virtual void gameResume() = 0;
    virtual void gameOver() = 0;
    virtual bool useObject(const std::string& Object) = 0;
};

#endif /*__RULE_H__*/


