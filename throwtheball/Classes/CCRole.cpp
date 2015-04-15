#include "CCRole.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CCRoleAdapter.h"
#include "CCHeroAdapterOfPhysics.h"
#include "CCSupportAdapterOfPhysics.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// on "init" you need to initialize your instance
bool SuperRole::init()
{
    auto frameCache = CCSpriteFrameCache::getInstance(); 
    if (nullptr == frameCache) { return false;}
    auto fileUtil = FileUtils::getInstance();
    std::string fliename(fileUtil->getWritablePath()+"appConfig.plist");
    if (fileUtil->isFileExist(fliename))
    {
        ValueMap appConfig = fileUtil->getValueMapFromFile(fliename);
    }
    

    frameCache->addSpriteFramesWithFile("Sprite/hero/hero.plist");
    frameCache->addSpriteFramesWithFile("Sprite/object/object.plist");

    auto spriteFrame = getSpriteFrameByRoleType();
    if ( !Sprite::initWithSpriteFrame(spriteFrame))
    {
        return false;
    }
    setAnchorPoint(Vec2(0.5f,0.0f));
    auto physicalBody = PhysicsBody::createBox(spriteFrame->getOriginalSize(), PhysicsMaterial(10.0f, 0.0f, 0.0F));
    setPhysicsBody(physicalBody);
    //只注册一次，不要多次注册，不然会引起充分删除崩溃
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = SuperRole::onContactBegin;
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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
            framePath = "Sprite/object/Hydrangea1.png";
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

bool SuperRole::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto ptr_NodeA = dynamic_cast<SuperRole*>(contact.getShapeA()->getBody()->getNode());
    auto ptr_NodeB = dynamic_cast<SuperRole*>(contact.getShapeB()->getBody()->getNode());
    if (nullptr == ptr_NodeA &&
        nullptr == ptr_NodeB)
    {
        return true;
    }
    //碰撞边界
    else if (nullptr != ptr_NodeA && nullptr == ptr_NodeB)
    {
        auto UserObject = ptr_NodeA->getUserObject();
        if (nullptr != UserObject)
        {
            //防止传进去的参数被释放
            ptr_NodeA->retain();
            UserObject->retain();
            auto SupportAdapet = dynamic_cast<CCSupportAdapter*>(UserObject);
            if (nullptr != SupportAdapet)
            {
                CCSupportAdapter::s_onObjectContactBottom(SupportAdapet);
            }
            UserObject->release();
            ptr_NodeA->release();
        }
        return true;
    }
    //碰撞边界
    else if (nullptr != ptr_NodeB && nullptr == ptr_NodeA)
    {
        auto UserObject = ptr_NodeB->getUserObject();
        if (nullptr != UserObject)
        {
            //防止传进去的参数被释放
            UserObject->retain();
            auto SupportAdapet = dynamic_cast<CCSupportAdapter*>(UserObject);
            if (nullptr != SupportAdapet)
            {
                CCSupportAdapter::s_onObjectContactBottom(SupportAdapet);
            }
            UserObject->release();
        }
        return true;
    }
    else
    {
        //碰撞配角
        if (MAIN_HERO == ptr_NodeA->getType())
        {
            auto heroAdapet     = dynamic_cast<CCHeroAdapter*>(ptr_NodeA->getUserObject());
            auto SupportAdapet  = dynamic_cast<CCSupportAdapter*>(ptr_NodeB->getUserObject());
            if (nullptr != heroAdapet &&
                nullptr != SupportAdapet &&
                nullptr != CCHeroAdapter::s_onHeroContact)
            {
                CCHeroAdapter::s_onHeroContact(heroAdapet,SupportAdapet);
            }
            return false;
        }
        else if (MAIN_HERO == ptr_NodeB->getType())
        {
            auto heroAdapet     = dynamic_cast<CCHeroAdapter*>(ptr_NodeB->getUserObject());
            auto SupportAdapet  = dynamic_cast<CCSupportAdapter*>(ptr_NodeA->getUserObject());
            if (nullptr != heroAdapet &&
                nullptr != SupportAdapet &&
                nullptr != CCHeroAdapter::s_onHeroContact)
            {
                CCHeroAdapter::s_onHeroContact(heroAdapet,SupportAdapet);
            }
            return false;
        }
        return true;
    }
}


bool CCHero::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    
    //此处设置主角被所有东西碰撞，但下落物体自己不碰撞
    auto hysicsBody = getPhysicsBody();
    if (nullptr != hysicsBody)
    {
        hysicsBody->setCategoryBitmask(0x4);
        hysicsBody->setContactTestBitmask(0x2);
        hysicsBody->setCollisionBitmask(0x4);
        hysicsBody->setDynamic(false);
    }
    auto adapter = CCHeroAdapterOfPhysics::create();
    adapter->setHero(this);
    setUserObject(adapter);
    setName("Hero");
    return true;
}

//配角类
bool CCSupport::init()
{
    if (!SuperRole::init())
    {
        return false;
    }
    auto support = CCSupportAdapterOfPhysics::create();
    support->setSupport(this);
    setUserObject(support);

    auto hysicsBody = getPhysicsBody();
    if (nullptr != hysicsBody)
    {
        hysicsBody->setCategoryBitmask(0x12);
        hysicsBody->setContactTestBitmask(0x5);
        hysicsBody->setCollisionBitmask(0x9);
    }

    return true;
}

//绣球类实现

bool CCHydrangea::init()
{
    if (!CCSupport::init())
    {
        return false;
    }
    setName("Hydrangea");
    return true;
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
