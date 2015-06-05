#ifndef __DEFINE_H__
#define __DEFINE_H__
#include "cocos2d.h"

enum RoleType :int
{
    Default = -1,
    MAIN_HERO,                  //����
    DAMAGE_TILE,                //��Ƭ
    DAMAGE_BAD_EGG,             //������
    DAMAGE_SMELLY_STOCKINGS,    //������
    DAMAGE_BAD_VEGETABLE,       //����Ҷ
    GAIN_SACHET,                //����
    GAIN_HANDKERCHIEF,          //����
    GAIN_JADE_PENDANT,          //����
    GAIN_JADE,                  //����
    GAIN_CLOCK                  //ʱ��
};  
const char SZFACEPATH[] = {"Layer/Headshot/Hero/face.png"};
#define CC_ATTRIBUTE(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void)  { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }
#endif // __DEFINE_H__