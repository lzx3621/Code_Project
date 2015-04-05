#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCRoleFactoryOfObject.h"
USING_NS_CC;

using namespace cocostudio::timeline;

//Role类工厂，用于创建角色对象，返回超类的引用对象

SuperRole* CCRoleFactoryOfObject::createRoleForObject( RoleType Type, const Vec2 &pos )
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
        _parents->addChild(ptr_Rtn);
        ptr_Rtn->setPosition(pos);
    }
    return ptr_Rtn;
}

bool CCRoleFactoryOfObject::init()
{
    return true;
}

ptr_RoleFactory CCRoleFactoryOfObject::create( cocos2d::Node* const &parents )
{
    if ( nullptr == parents) 
    {
        return ptr_RoleFactory(nullptr);
    }
    auto instance = ptr_RoleFactory(new(std::nothrow) CCRoleFactoryOfObject(parents));
    instance->init();
    return instance;
}

CCRoleAdapter* CCRoleFactoryOfObject::getRoleAdapter( cocos2d::Sprite* factoryCreate )
{
    return nullptr;
}
