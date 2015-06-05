#include "CCSupport.h"
#include "Adapter/CCSupportAdapterOfPhysics.h"
#include "AppConfig/CCAppConfig.h"
USING_NS_CC;

//配角类
bool CCSupport::init()
{
    auto spriteFrame = getSpriteFrameByRoleType();
    if (nullptr == spriteFrame ||
        !SuperRole::init()||
        !Sprite::init())
    {
        return false;
    }
    setSpriteFrame(spriteFrame);
    auto physicalBody = PhysicsBody::createBox(spriteFrame->getOriginalSize(), PhysicsMaterial(10.0f, 0.0f, 0.0F));
    //此处设置主角被所有东西碰撞，但下落物体自己不碰撞
    if (nullptr != physicalBody)
    {
        physicalBody->setCategoryBitmask(10);
        physicalBody->setContactTestBitmask(5);
        physicalBody->setCollisionBitmask(8);
        //physicalBody->setDynamic(false);
        setPhysicsBody(physicalBody);
    }
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(CCSupport::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool CCSupport::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto ptr_NodeA = contact.getShapeA()->getBody()->getNode();
    auto ptr_NodeB = contact.getShapeB()->getBody()->getNode();
    if (ptr_NodeA && ptr_NodeB)
    {
        CCLOG("CCSupport ptr_NodeA Name: %s, ptr_NodeB: %s",
            ptr_NodeA->getName().c_str(),
            ptr_NodeB->getName().c_str());
    }
    auto pthis = (ptr_NodeA == this)?this:(ptr_NodeB == this?this:nullptr);
    if (nullptr == pthis)
    {
        return true;
    }
    auto other = (ptr_NodeA != this)?ptr_NodeA:ptr_NodeB;
    if (nullptr != other && "wall" != other->getName())
    {
        return true;
    }

    auto SupportAdapet = dynamic_cast<CCSupportAdapter*>(CCSupportAdapterOfPhysics::create(this));
    if (nullptr != SupportAdapet)
    {
        SupportAdapet->s_onObjectContactBottom(*SupportAdapet);
    }
    return true;
}

cocos2d::SpriteFrame* CCSupport::getSpriteFrameByRoleType()
{
    std::string framePath;

    switch (_roleType)
    {
    case DAMAGE_TILE:
        framePath = "Sprite/object/tile.png";
        break;
    case DAMAGE_BAD_EGG:
        framePath = "Sprite/object/badegg.png";
        break;
    case DAMAGE_SMELLY_STOCKINGS:
        framePath = "Sprite/object/smellystockings.png";
        break;
    case DAMAGE_BAD_VEGETABLE:
        framePath = "Sprite/object/badvegetable.png";
        break;
    case GAIN_SACHET:
        framePath = "Sprite/object/sachet.png";
        break;
    case GAIN_HANDKERCHIEF:
        framePath = "Sprite/object/handkerchief.png";
        break;
    case GAIN_JADE_PENDANT:
        framePath = "Sprite/object/jadependant.png";
        break;
    case GAIN_JADE:
        framePath = "Sprite/object/jade.png";
        break;
    case GAIN_CLOCK:
        framePath = "Sprite/object/clock.png";
        break;
    default:
        break;
    }

    if (framePath.empty())
    {
        CCLOGERROR("RoleType :%d", _roleType);
        return nullptr;
    }
    auto ret = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(framePath);
    if (ret)
    {
        CCLOGERROR("RoleType :%d, framePath: %s", _roleType, framePath.c_str());
    }
    return ret;
}

void CCSupport::pause(void)
{
    Sprite::pause();
    if (_vectTemp == Vect::ZERO)
    {
        _vectTemp = getPhysicsBody()->getVelocity();
        getPhysicsBody()->setVelocity(Vect::ZERO);
    }
}

void CCSupport::resume(void)
{
    Sprite::resume();
    if (_vectTemp != Vect::ZERO)
    {
        getPhysicsBody()->setVelocity(_vectTemp);
        _vectTemp = Vect::ZERO;
    }
}

//瓦片类实现

bool CCTile::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Tile");
    return true;
}

//臭鸡蛋类实现

bool CCBadGgg::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("BadGgg");
    return true;
}

//臭袜子类实现

bool CCSmellyStockings::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("SmellyStockings");
    return true;
}

////栏菜叶类实现

bool CCBadVegetable::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("BadVegetable");
    return true;
}

//香囊类实现

bool CCSachet::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Sachet");
    return true;
}

//手帕类实现

bool CCHandkerchief::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Handkerchief");
    return true;
}

//玉佩类实现

bool CCJadePendant::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("JadePendant");
    return true;
}

//如意类实现

bool CCJade::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Jade");
    return true;
}

bool CCClock::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Clock");
    return true;
}
