#include "CCRole.h"
#include "CCRoleFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//Role类工厂，用于创建角色对象，返回超类的引用对象

Sprite* CCRoleFactoryOfObject::createRoleForObject( RoleType Type, Node* const &Mount )
{
    SuperRole *ptr_Rtn = nullptr;
    switch(Type)
    {
    case MAIN_HERO:
        ptr_Rtn = CChero::create();
        break;
    case DAMAGE_HYDRANGEA:
        ptr_Rtn = CCHydrangea::create();
        break;
    case DAMAGE_TILE:
        ptr_Rtn = CCHydrangea::create();
        break;
    case DAMAGE_BAD_EGG:
        ptr_Rtn = CCHydrangea::create();
        break;
    case DAMAGE_SMELLY_STOCKINGS:
        ptr_Rtn = CCHydrangea::create();
        break;
    case DAMAGE_BAD_VEGETABLE:
        ptr_Rtn = CCHydrangea::create();
        break;
    case GAIN_SACHET:
        ptr_Rtn = CCHydrangea::create();
        break;
    };
    if (nullptr != ptr_Rtn)
    {
        Mount->addChild(ptr_Rtn);
    }
    return ptr_Rtn;
}
