#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"

/************************************************************************/
/* 定义规则使用，决定游戏如何进行                                       */
/************************************************************************/
class CCRule /*:public cocos2d::Node*/
{
protected:
    CCRule(void){}
    ~CCRule(void){}
//     virtual bool init() override
//     {
//         if (cocos2d::Node::init())
//         {
//             cocos2d::Node::setName("Rule");
//             return true;
//         }
//         else
//         {
//             return false;
//         }
//     }
public:
    virtual void gameStart() = 0;
    virtual void gameRestart() = 0;
    virtual void gamePause() = 0;
    virtual void gameOver() = 0;
};

#endif __RULE_FACTORY_H__


