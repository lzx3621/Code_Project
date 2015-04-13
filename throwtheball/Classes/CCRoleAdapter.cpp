#include "CCRoleAdapter.h"

onHeroContact CCHeroAdapter::s_onHeroContact = nullptr;

onObjectContactBottom CCSupportAdapter::s_onObjectContactBottom = nullptr; 

void CCHeroAdapter::setHeroContactCallback(onHeroContact HeroContact)
{
    s_onHeroContact = HeroContact;
}

void CCSupportAdapter::setObjectContactBottomCallback(onObjectContactBottom ObjectContactBottom)
{
    s_onObjectContactBottom = ObjectContactBottom;
}
