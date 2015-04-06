#include "CCNormalRule.h"
#include "CCRoleFactoryOfObject.h"

USING_NS_CC;

CCNormalRule::CCNormalRule(void)
{
}


CCNormalRule::~CCNormalRule(void)
{
}


CCNormalRule* CCNormalRule::create( cocos2d::Node* const parent )
{
    auto *pRet = new(std::nothrow) CCNormalRule(); 
    if (pRet ) 
    { 
        parent->addChild(pRet);
        if (!pRet->init())
        {
            parent->removeChild(pRet);
            delete pRet; 
            pRet = NULL; 
            return NULL;
        }
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

void CCNormalRule::onHeroContact( cocos2d::Sprite* Hero, cocos2d::Sprite* Contact, const int& iHerolive, const int& iHeroScore )
{

}

void CCNormalRule::onStart()
{
    /*_heroSprite =*/ 
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
            _roleFactory = CCRoleFactoryOfObject::create(getParent());
        }
        auto hero = _roleFactory->createRole(MAIN_HERO, Vec2(200,3));
        return true;
    }
    else
    {
        return false;
    }
}
