#include "CCHeroAdapterOfPhysics.h"
#include "CCRole.h"

USING_NS_CC;

CCHeroAdapterOfPhysics::CCHeroAdapterOfPhysics(void)
{
}


CCHeroAdapterOfPhysics::~CCHeroAdapterOfPhysics(void)
{
}

bool CCHeroAdapterOfPhysics::init()
{
    return true;
}

Sprite* CCHeroAdapterOfPhysics::getSprite()
{
    return _hero;
}

int CCHeroAdapterOfPhysics::getOriginLive()
{
    return _hero->getOriginLive();
}

int CCHeroAdapterOfPhysics::getOriginScore()
{
    return _hero->getOriginScore();
}

int CCHeroAdapterOfPhysics::getCurrentLive()
{
    return _hero->getLive();
}

void CCHeroAdapterOfPhysics::setCurrentLive(const int & val)
{
    _hero->setLive(val);
}

void CCHeroAdapterOfPhysics::setCurrentScore(const int & val)
{
    _hero->setScore(val);
}

int CCHeroAdapterOfPhysics::getCurrentScore()
{
    return _hero->getScore();
}

void CCHeroAdapterOfPhysics::setHero(CCHero* hero)
{
    _hero = hero;
}

