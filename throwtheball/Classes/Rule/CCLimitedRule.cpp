#include "CCLimitedRule.h"
#include "Role/CCRoleFactory.h"
#include "Adapter/CCRoleAdapter.h"
#include "Adapter/CCGameUIAdapter.h"
#include "AppConfig/CCAppConfig.h"

USING_NS_CC;

CCLimitedRule::CCLimitedRule():
    _time(59)
{
    CCLOG("CCLimitedRule create");
}

CCLimitedRule::~CCLimitedRule(void)
{
    CCLOG("CCLimitedRule delete");
}

bool CCLimitedRule::init(CCGameUIAdapter* UIAdapter)
{
    CCNormalRule::init(UIAdapter);
    _UIAdapter->setlimited(true);
    return true;
}

bool CCLimitedRule::isGameContinue(CCHeroAdapter &hero, CCSupportAdapter &support)
{
    auto Score = hero.getCurrentScore();
    _storeUp += (support.getPropertyOfScore()>0?support.getPropertyOfScore():0);
    if (_storeUp > 1750)
    {
        auto level = _level;
        setLevel(++level);
        _storeUp = 0;
    }
    return true;
}

void CCLimitedRule::gameStart()
{
    CCNormalRule::gameStart();
    _gameScene->schedule(CC_CALLBACK_1(CCLimitedRule::countDown, this), 1, "countdown");
}

void CCLimitedRule::gameRestart()
{
    _time = 59;
    CCNormalRule::gameRestart();
    unschedule("countdown");
    schedule(CC_CALLBACK_1(CCLimitedRule::countDown, this), 1, "countdown");
}

CCNormalRule* CCLimitedRule::create(CCGameUIAdapter* UIAdapter)
{
    auto *pRet = new(std::nothrow) CCLimitedRule(); 
    if (pRet && pRet->init(UIAdapter)) 
    { 
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

void CCLimitedRule::countDown(float d)
{
    auto i = --_time;
    _UIAdapter->updateTime(i);
    if (_time <= 0)
    {
        gameOver();
        unschedule("countdown");
    }
}

bool CCLimitedRule::useObject(const std::string& Object)
{
    if (!CCNormalRule::useObject(Object))
    {
        if ("clock" == Object)
        {
            auto clock = CCAppConfig::getInstance()->getObjectClock()-1;
            if (clock >= 0)
            {
                _time += 5;
                auto i = _time;
                _UIAdapter->updateTime(i);
                CCAppConfig::getInstance()->setObjectClock(clock);
                return true;
            }
        }
        return false;
    }
    else
    {
        return true;
    }
}

void CCLimitedRule::createObjectOffFall(float dt)
{
    auto ran = cocos2d::random(1,3);
    for (int i = 0; i < ran; i++)
    {
        auto role = (RoleType)cocos2d::random<int>((int)DAMAGE_BAD_EGG, (int)GAIN_CLOCK);
        if (role == GAIN_CLOCK)
        {
            if (1 == cocos2d::random(1,3))
            {
                addRole(role);
                continue;
            }
            else
            {
                role = (RoleType)cocos2d::random<int>((int)DAMAGE_BAD_EGG, (int)GAIN_CLOCK);
            }
        }
        addRole(role);
    }
}

void CCLimitedRule::onHeroContact(CCHeroAdapter& hero, CCSupportAdapter& support)
{
    if ("Clock" == support.getSprite()->getName())
    {
        _time += 5;
    }
    CCNormalRule::onHeroContact(hero, support);
}
