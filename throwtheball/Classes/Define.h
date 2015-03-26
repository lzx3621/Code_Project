#ifndef __DEFINE_H__
#define __DEFINE_H__
#include "cocos2d.h"

typedef std::function<void(cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore)> HeroContact;

enum RoleType
{
    Default = -1,
    MAIN_HERO,                  //����
    DAMAGE_HYDRANGEA,           //����
    DAMAGE_TILE,                //��Ƭ
    DAMAGE_BAD_EGG,             //������
    DAMAGE_SMELLY_STOCKINGS,    //������
    DAMAGE_BAD_VEGETABLE,       //����Ҷ
    GAIN_SACHET,                //����
    GAIN_HANDKERCHIEF,          //����
    GAIN_JADE_PENDANT,          //����
    GAIN_JADE                   //����
};  

#endif // __DEFINE_H__