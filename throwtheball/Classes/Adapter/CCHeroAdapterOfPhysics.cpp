#include "CCHeroAdapterOfPhysics.h"
#include "Role/CCHero.h"

USING_NS_CC;

CCHeroAdapterOfPhysics::CCHeroAdapterOfPhysics(CCHero* hero):
    _hero(hero)
{
}


CCHeroAdapterOfPhysics::~CCHeroAdapterOfPhysics(void)
{
    CC_SAFE_RELEASE_NULL(_hero);
}

bool CCHeroAdapterOfPhysics::init()
{
    if (nullptr == _hero)
    {
        CCLOGERROR("CCHeroAdapterOfPhysics _hero is Null!");
        return false;
    }
    _hero->retain();
    return true;
}

cocos2d::Sprite* CCHeroAdapterOfPhysics::getHero()
{
    return static_cast<Sprite*>(_hero);
}


int CCHeroAdapterOfPhysics::getCurrentLive()
{
    return /*dynamic_cast<SuperRole*>*/(_hero)->getLive();
}

void CCHeroAdapterOfPhysics::setCurrentLive(const unsigned int & val)
{
    _hero->setLive(val);
}

void CCHeroAdapterOfPhysics::setCurrentScore(const unsigned int & val)
{
    _hero->setScore(val);
}

int CCHeroAdapterOfPhysics::getCurrentScore()
{
    return _hero->getScore();
}

CCHeroAdapterOfPhysics* CCHeroAdapterOfPhysics::create(CCHero* hero)
{
    auto *pRet = new(std::nothrow) CCHeroAdapterOfPhysics(hero); 
    if (pRet && pRet->init()) 
    { 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}


