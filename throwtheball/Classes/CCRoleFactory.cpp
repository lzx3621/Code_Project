#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCRoleFactory.h"
USING_NS_CC;

//Role类工厂，用于创建角色对象，返回超类的引用对象
SuperRole* CCRoleFactory::createRoleOfPhysics( RoleType Type, const cocos2d::Vec2 &pos )
{
    SuperRole *ptr_Rtn = nullptr;
    switch(Type)
    {
    case MAIN_HERO:
        ptr_Rtn = CCHero::create();
        break;
    case DAMAGE_HYDRANGEA:
        ptr_Rtn = CCHydrangea::create();
        break;
    case DAMAGE_TILE:
        ptr_Rtn = CCTile::create();
        break;
    case DAMAGE_BAD_EGG:
        ptr_Rtn = CCBadGgg::create();
        break;
    case DAMAGE_SMELLY_STOCKINGS:
        ptr_Rtn = CCSmellyStockings::create();
        break;
    case DAMAGE_BAD_VEGETABLE:
        ptr_Rtn = CCBadVegetable::create();
        break;
    case GAIN_SACHET:
        ptr_Rtn = CCSachet::create();
        break;
    case GAIN_HANDKERCHIEF:
        ptr_Rtn = CCHandkerchief::create();
        break;
    case GAIN_JADE_PENDANT:
        ptr_Rtn = CCJadePendant::create();
        break;
    case GAIN_JADE:
        ptr_Rtn = CCJade::create();
        break;
    default:
        CCLOG("error input RoleType");
        break;
    };
    if (nullptr != ptr_Rtn)
    {
		getScene()?getScene()->addChild(ptr_Rtn):CCLOG("no mount scene!");
        ptr_Rtn->setPosition(pos);
    }
    return ptr_Rtn;
}
//自动挂载到父节点的场景，如果没有场景，返回未挂载的
Sprite* CCRoleFactory::createRole( RoleType Type, const cocos2d::Vec2 &pos /*= Vec2(0,0)*/)
{
	if (nullptr != this->getScene())
	{
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
	else
	{
		return createRoleOfPhysics(Type, pos);
	}
}
// 
// bool CCRoleFactory::init()
// {
//     cocos2d::Node::init();
//     return true;
// }
