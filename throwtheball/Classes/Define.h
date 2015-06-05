#ifndef __DEFINE_H__
#define __DEFINE_H__
#include "cocos2d.h"

enum RoleType :int
{
    Default = -1,
    MAIN_HERO,                  //÷˜Ω«
    DAMAGE_TILE,                //Õﬂ∆¨
    DAMAGE_BAD_EGG,             //≥Ùº¶µ∞
    DAMAGE_SMELLY_STOCKINGS,    //≥ÙÕ‡◊”
    DAMAGE_BAD_VEGETABLE,       //¿∏≤À“∂
    GAIN_SACHET,                //œ„ƒ“
    GAIN_HANDKERCHIEF,          // ÷≈¡
    GAIN_JADE_PENDANT,          //”Ò≈Â
    GAIN_JADE,                  //»Á“‚
    GAIN_CLOCK                  // ±÷”
};  
const char SZFACEPATH[] = {"Layer/Headshot/Hero/face.png"};
#define CC_ATTRIBUTE(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void)  { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }
#endif // __DEFINE_H__