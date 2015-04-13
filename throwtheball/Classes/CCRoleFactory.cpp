#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCRoleFactory.h"
USING_NS_CC;

using namespace cocostudio::timeline;

//Role类工厂，用于创建角色对象，返回超类的引用对象

SuperRole* CCRoleFactory::createRoleOfPhysics( RoleType Type, const Vec2 &pos )
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
        getParent()->addChild(ptr_Rtn);
        ptr_Rtn->setPosition(pos);
    }
    return ptr_Rtn;
}


CCRoleAdapter* CCRoleFactory::getRoleAdapter( cocos2d::Sprite* factoryCreate )
{

    return nullptr;
}


Sprite* CCRoleFactory::createRole( RoleType Type, const cocos2d::Vec2 &pos )
{
    if (nullptr == getParent())
    {
        CCLOG("Parent is null, can\'t not create Role! please set parent for it.");
        return nullptr;
    }
    auto physicsWorld = this->getScene()->getPhysicsWorld();
    if (nullptr != physicsWorld)
    {
        //物理世界不是同一个的时候，需要一个添加一个底部精灵来判断物体下落到底的消失事件
        if (_physicsWorld != physicsWorld)
        {
            //getParent()->addChild(Sprite::create("",))
        }
        return createRoleOfPhysics(Type, pos);
    }
    else
    {
        //未完成
        return nullptr;
    }
}

bool CCRoleFactory::init()
{
    cocos2d::Node::init();
//     getEventDispatcher()->addCustomEventListener("setParent",[=](EventCustom* event){
//         if ("setParent" == event->getEventName() &&
//             nullptr != event->getCurrentTarget()->getScene()->getPhysicsWorld())
//         {
//             CCLOG("getScene() is a Physics Scene.");
//         }
//     });
    return true;
}
