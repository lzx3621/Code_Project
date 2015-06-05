#include "CCRoleFactory.h"
#include "CCHero.h"
#include "CCSupport.h"
USING_NS_CC;

//Role�๤�������ڴ�����ɫ���󣬷��س�������ö���
SuperRole* CCRoleFactory::createRoleOfPhysics( RoleType Type, const cocos2d::Point &pos )
{
    SuperRole *ptr_Rtn = nullptr;
    switch(Type)
    {
    case MAIN_HERO:
        ptr_Rtn = CCHero::create();
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
    case GAIN_CLOCK:
        ptr_Rtn = CCClock::create();
        break;
    default:
        CCLOGERROR("error input RoleType");
        break;
    };
    if (nullptr != ptr_Rtn)
    {
        dynamic_cast<Sprite*>(ptr_Rtn)->setPosition(pos);
    }
    return ptr_Rtn;
}
//�Զ����ص����ڵ�ĳ��������û�г���������δ���ص�
cocos2d::Sprite* CCRoleFactory::createRole( RoleType Type, const cocos2d::Point &pos /*= cocos2d::Point(0,0)*/)
{
	return dynamic_cast<Sprite*>(createRoleOfPhysics(Type, pos));
}

