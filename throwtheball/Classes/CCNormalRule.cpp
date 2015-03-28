#include "CCNormalRule.h"


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
    _heroSprite = _roleFactory->createRole(MAIN_HERO, _gameScene);
    _roleFactory->createRole(cocos2d::random(DAMAGE_HYDRANGEA, GAIN_JADE), _gameScene);
}

void CCNormalRule::onPause()
{

}

void CCNormalRule::onEnd()
{

}
