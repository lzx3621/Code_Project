#ifndef __DEFINE_H__
#define __DEFINE_H__
#include "cocos2d.h"

typedef std::function<void(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore)> HeroContact;

enum RoleType
{
    Default = -1,
    MAIN_HERO,                  //÷˜Ω«
    DAMAGE_HYDRANGEA,           //–Â«Ú
    DAMAGE_TILE,                //Õﬂ∆¨
    DAMAGE_BAD_EGG,             //≥Ùº¶µ∞
    DAMAGE_SMELLY_STOCKINGS,    //≥ÙÕ‡◊”
    DAMAGE_BAD_VEGETABLE,       //¿∏≤À“∂
    GAIN_SACHET,                //œ„ƒ“
    GAIN_HANDKERCHIEF,          // ÷≈¡
    GAIN_JADE_PENDANT,          //”Ò≈Â
    GAIN_JADE                   //»Á“‚
};  

#endif // __DEFINE_H__