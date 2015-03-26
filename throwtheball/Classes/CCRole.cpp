#include "CCRole.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// on "init" you need to initialize your instance
bool SuperRole::init()
{
    auto heroCache = CCSpriteFrameCache::getInstance(); 
    if (nullptr == heroCache) { return false;}
    auto fileUtil = FileUtils::getInstance();
    std::string fliename(fileUtil->getWritablePath()+"appConfig.plist");
    if (fileUtil->isFileExist(fliename))
    {
        ValueMap appConfig = fileUtil->getValueMapFromFile(fliename);
    }
    

    heroCache->addSpriteFramesWithFile("Sprite/hero/hero.plist");
    heroCache->addSpriteFramesWithFile("Sprite/object/object.plist");

    if ( !Sprite::initWithSpriteFrame(getSpriteFrameByRoleType()))
    {
        return false;
    }
    auto physicalBody = PhysicsBody::createBox(getSpriteFrameByRoleType()->getOriginalSize(), PhysicsMaterial(1.0f, 0.0f, 0.5F));
    setPhysicsBody(physicalBody);
    return true;
}

SpriteFrame* SuperRole::getSpriteFrameByRoleType()
{
    std::string framePath;

    switch (_roleType)
    {
    case MAIN_HERO:
        CCUserDefault::getInstance()->getStringForKey("HeroFrameName", framePath);
        if ("" == framePath)
        {
            framePath = "Sprite/hero/waiter.png";
        }
        break;
    case DAMAGE_HYDRANGEA:
        CCUserDefault::getInstance()->getStringForKey("HydrangeaFrameName", framePath);
        if ("" == framePath)
        {
            framePath = "Sprite/hero/Hydrangea1.png";
        }
        break;
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
    default:
        break;
    }
    return framePath.empty()?nullptr:CCSpriteFrameCache::getInstance()->getSpriteFrameByName(framePath);
}


bool CChero::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    
    //此处设置主角被所有东西碰撞，但下落物体自己不碰撞
    getPhysicsBody()->setCategoryBitmask(0x01);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x01);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(CChero::onContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    setName("Hero");
    return true;
}



//主角类实现

bool CChero::onContactBegin( PhysicsContact& contact )
{
    auto ptr_NodeA = dynamic_cast<SuperRole*>(contact.getShapeA()->getBody()->getNode());
    auto ptr_NodeB = dynamic_cast<SuperRole*>(contact.getShapeB()->getBody()->getNode());
    if (nullptr == ptr_NodeA && nullptr == ptr_NodeB)
    {
        return false;
    }
    if (MAIN_HERO == ptr_NodeA->getType())
    {
        ptr_NodeA->_live += ptr_NodeB->_live;
        ptr_NodeA->_score += ptr_NodeB->_score;
        _onHeroContact(ptr_NodeA, ptr_NodeB, ptr_NodeA->_live, ptr_NodeA->_score);
    }
    if (MAIN_HERO == ptr_NodeB->getType())
    {
        ptr_NodeB->_live += ptr_NodeA->_live;
        ptr_NodeB->_score += ptr_NodeA->_score;
        _onHeroContact(ptr_NodeB, ptr_NodeA, ptr_NodeB->_live, ptr_NodeB->_score);
    }
    
    return true;
}

//绣球类实现

bool CCHydrangea::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("Hydrangea");
    return true;
}

bool CCTile::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("Tile");
    return true;
}

bool CCBadGgg::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("BadGgg");
    return true;
}

bool CCSmellyStockings::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("SmellyStockings");
    return true;
}

bool CCBadVegetable::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("BadVegetable");
    return true;
}

bool CCSachet::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("Sachet");
    return true;
}

bool CCHandkerchief::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("Handkerchief");
    return true;
}

bool CCJadePendant::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("JadePendant");
    return true;
}

bool CCJade::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    //要设置同物体可以不相碰，但主角要相碰
    getPhysicsBody()->setCategoryBitmask(0x10);
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x100);
    setName("Jade");
    return true;
}
