#include "CCRole.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Adapter/CCRoleAdapter.h"
#include "Adapter/CCHeroAdapterOfPhysics.h"
#include "Adapter/CCSupportAdapterOfPhysics.h"
#include "AppConfig/CCAppConfig.h"
#include "Expand/Hero/CCHeroEvent.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// on "init" you need to initialize your instance
bool SuperRole::init()
{
    auto frameCache = CCSpriteFrameCache::getInstance(); 
    if (nullptr == frameCache) { return false;}

    frameCache->addSpriteFramesWithFile("Sprite/hero/hero.plist");
    frameCache->addSpriteFramesWithFile("Sprite/object/object.plist");
    return true;
}

// void CCHero::setPosition(float x, float y)
// {
//     pos.x = x;
//     pos.y = y;
// }

