#include "CCNormalRule.h"
#include "CCRoleFactory.h"

USING_NS_CC;

CCNormalRule::CCNormalRule(void)
{
}


CCNormalRule::~CCNormalRule(void)
{
}

void CCNormalRule::onHeroContact( cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore )
{

}

void CCNormalRule::onStart()
{
    /*_heroSprite =*/ 
    _roleFactory->createRole(MAIN_HERO, Vec2(200,3));
    this->schedule(CC_CALLBACK_1(CCNormalRule::createObjectOffFall, this), 5.0f, CC_REPEAT_FOREVER, 0, std::string("createObjectOffFall"));
    
}

void CCNormalRule::onRestat()
{

}

void CCNormalRule::onPause()
{

}

void CCNormalRule::onEnd()
{

}

void CCNormalRule::createObjectOffFall( float dt )
{
    if (nullptr == _roleFactory)
    {
        return ;
    }
    _roleFactory->createRole((RoleType)cocos2d::random((int)DAMAGE_HYDRANGEA, (int)GAIN_JADE), Vec2(200,1000));
}

bool CCNormalRule::init()
{
    if (CCRule::init())
    {
        if (nullptr == _roleFactory)
        {
            _roleFactory = CCRoleFactory::create();
        }
        addChild(_roleFactory);

        return true;
    }
    else
    {
        return false;
    }
}

bool CCNormalRule::onHeroTouch(Touch* touch, Event* event)
{
    /*event->*/
    _hero->getSprite()->setPositionX(touch->getLocation().x);
    return true;
}
