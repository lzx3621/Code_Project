#include "CCSupportAdapterOfPhysics.h"

USING_NS_CC;

CCSupportAdapterOfPhysics::CCSupportAdapterOfPhysics(void)
{
}


CCSupportAdapterOfPhysics::~CCSupportAdapterOfPhysics(void)
{
}


bool CCSupportAdapterOfPhysics::init()
{
    return true;
}

Sprite* CCSupportAdapterOfPhysics::getSprite()
{
    return _support;
}

int CCSupportAdapterOfPhysics::getPropertyOfLive()
{
    return _support->getLive();
}

int CCSupportAdapterOfPhysics::getPropertyOfScore()
{
    return _support->getScore();
}
 
RoleType CCSupportAdapterOfPhysics::getType()
{
    return _support->getType();
}

void CCSupportAdapterOfPhysics::setSupport(CCSupport* support)
{
    _support = support;
}
