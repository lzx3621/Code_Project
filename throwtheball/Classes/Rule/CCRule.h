#ifndef __RULE_FACTORY_H__
#define __RULE_FACTORY_H__

#include "cocos2d.h"

/************************************************************************/
/* �������ʹ�ã�������Ϸ��ν���                                       */
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
};

#endif __RULE_FACTORY_H__

