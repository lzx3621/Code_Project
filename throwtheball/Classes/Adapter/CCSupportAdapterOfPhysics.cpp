#include "CCSupportAdapterOfPhysics.h"
#include "Role/CCSupport.h"
USING_NS_CC;

CCSupportAdapterOfPhysics::CCSupportAdapterOfPhysics(CCSupport* support):
    _support(support)
{
}


CCSupportAdapterOfPhysics::~CCSupportAdapterOfPhysics(void)
{
    CC_SAFE_RELEASE_NULL(_support);
}


bool CCSupportAdapterOfPhysics::init()
{
    if (nullptr == _support)
    {
        CCLOGERROR("CCSupportAdapterOfPhysics _hero is Null!");
        return false;
    }
    _support->retain();
    return true;
}

Sprite* CCSupportAdapterOfPhysics::getSprite()
{
    return dynamic_cast<Sprite*>(_support);
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

CCSupportAdapterOfPhysics* CCSupportAdapterOfPhysics::create(CCSupport* support)
{
    auto *pRet = new(std::nothrow) CCSupportAdapterOfPhysics(support); 
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
