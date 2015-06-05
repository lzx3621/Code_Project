#include "CCNormalRule.h"
#include "Role/CCRoleFactory.h"
#include "Adapter/CCRoleAdapter.h"
#include "Adapter/CCGameUIAdapter.h"
#include "AppConfig/CCAppConfig.h"
#include "Audio/CCAudioHelper.h"

USING_NS_CC;

CCNormalRule::CCNormalRule():
    _isStart(false),
    _gameScene(nullptr),
    _UIAdapter(nullptr),
    _level(0),
    _storeUp(0),
    _levelResume(0),
    _currScore(0),
    _pauseAllRole(false),
    _hero(nullptr),
    _numGain(0),
    _numDamage(0),
    ROLEMAX(3)
{
    CCLOG("CCNormalRule create");
}

CCNormalRule::~CCNormalRule(void)
{
    //CC_SAFE_RELEASE_NULL(_gameScene);
    CCLOG("CCNormalRule delete");
}

void CCNormalRule::gameStart()
{
    if (!_isStart)
    {
		_gameScene->schedule(CC_CALLBACK_1(CCNormalRule::createObjectOffFall, this),
			1.0f, 
			CC_REPEAT_FOREVER,
			0,
			std::string("createObjectOffFall"));
		_hero = _roleFactory->createRole(MAIN_HERO, Point(0,0));
        _UIAdapter->addRole(_hero);
        _hero->setPosition(_gameScene->getBoundingBox().size.width/2, 
            (_hero->getBoundingBox().size.height/2)+3);
		_isStart = true;
    }
    
}

void CCNormalRule::gameRestart()
{
    setLevel(1);
    _UIAdapter->removeAllRole();
    _pauseAllRole = false;
    _isStart = false;
    _gameScene->resume();
    _UIAdapter->hidePauseUI();
    _UIAdapter->hideHaze();
    _UIAdapter->hideGameOverUI();
    gameStart();
}

void CCNormalRule::gamePause()
{
    _UIAdapter->showPauseUI();
    pauseAllRole();
}

void CCNormalRule::gameResume()
{
    resumeAllRole();
    _UIAdapter->hidePauseUI();
    setLevel(_level);
}

void CCNormalRule::gameOver()
{
    if (true)
    {
        _hero->retain();
        _UIAdapter->removeAllRole();
        _UIAdapter->addRole(_hero);
        _hero->release();
        auto money = CCAppConfig::getInstance()->getMoney();
        money += (_currScore/100);
        money > 99999 ? money = 99999:money;
        CCAppConfig::getInstance()->setMoney(money);
        _gameScene->unschedule("createObjectOffFall");
        pauseAllRole();
        _UIAdapter->showGameOverUI(_currScore);
        _isStart = true;
    }
}
//不利的物品要在一边，不能再两个之间
void CCNormalRule::createObjectOffFall( float dt )
{
    if (nullptr == _roleFactory)
    {
        return ;
    }
    auto numGain = cocos2d::random<int>(0, ROLEMAX);
    auto numDamage = cocos2d::random<int>(0, ROLEMAX - _numGain);
    _numGain = numGain;
    _numDamage = numDamage;
    //分成numDamage+1区域
//     while (numDamage)
//     {
    auto ran = cocos2d::random(1,3);
    char szkey[10] = {0};
    for (int i = 0; i < ran; i++)
    {
        /*sprintf(szkey,"addRole_%d", i);
        schedule([=](float){*/
            addRole((RoleType)cocos2d::random<int>((int)DAMAGE_TILE, (int)GAIN_JADE));

        /*}, cocos2d::random<float>(0.1f, 1.0f), szkey);*/
    }
//     }
//     while (numGain)
//     {
//         addRole((RoleType)cocos2d::random<int>((int)GAIN_SACHET, (int)GAIN_JADE));
//     }
}

void CCNormalRule::addRole(RoleType type)
{
    auto role = _roleFactory->createRole(type);
    if (nullptr == role)
    {
        CCLOGERROR("can\'t not create role!");
        return ;
    }
    auto roleSize = role->getContentSize();
    auto apartLeftmin = roleSize.width/2;
    auto apartRightMax = _gameScene->getContentSize().width - (roleSize.width/2);
    auto height = _gameScene->getContentSize().height - (roleSize.height/2);
    role->setPosition(cocos2d::random<float>(apartLeftmin, apartRightMax), height-10);
    _UIAdapter->addRole(role);
}

bool CCNormalRule::init(CCGameUIAdapter* UIAdapter)
{
    _roleFactory = CCRoleFactory::create();
    _UIAdapter   = UIAdapter;
    if (nullptr == _UIAdapter ||
        nullptr == _UIAdapter->getGameScene() || 
        nullptr == _roleFactory ||
        !Node::init())
    {
        CCLOGERROR("CCNormalRule init error _UIAdapter:%d, getGameScene:%d _roleFactory%d",
            _UIAdapter, _UIAdapter->getGameScene(), _roleFactory);
        return false;
    }
    _gameScene = _UIAdapter->getGameScene();
    //_gameScene->retain();
    setName("Rule");
    CCHeroAdapter::setHeroContactCallback(CC_CALLBACK_2(CCNormalRule::onHeroContact, this));
    CCSupportAdapter::setObjectContactBottomCallback(CC_CALLBACK_1(CCNormalRule::onObjectContactBottom,this));
    _UIAdapter->setlimited(false);
    addChild(_roleFactory);
    setLevel(1);
    return true;
}

void CCNormalRule::onHeroContact(CCHeroAdapter& hero, CCSupportAdapter& support)
{
    auto sprite = support.getSprite();
    if (nullptr != sprite)
    {
        auto live = hero.getCurrentLive();
        auto score = hero.getCurrentScore();
        live += support.getPropertyOfLive();
        score += support.getPropertyOfScore();
        hero.setCurrentLive(live<0?live = 0:live);
        hero.setCurrentScore(score<0?score = 0:score);
        _currScore = score;
        _UIAdapter->updateHeroScoreAndLive(live, score);
        if (DAMAGE_TILE == support.getType())
        {
            CCAudioHelper::getInstance()->playEffect(5);
        }
        if (GAIN_HANDKERCHIEF == support.getType())
        {
            CCAudioHelper::getInstance()->playEffect(4);
        }
        if (!isGameContinue(hero, support))
        {
            gameOver();
        }
        if (1 == cocos2d::random(0,9))
        {
            _UIAdapter->showHaze();
        }
        sprite->removeFromParent();
    }
}

void CCNormalRule::onObjectContactBottom(CCSupportAdapter& support)
{
    auto sprite = support.getSprite();
    if (nullptr != sprite)
    {
        sprite->removeFromParent();
    }
}

CCNormalRule* CCNormalRule::create(CCGameUIAdapter* UIAdapter)
{
    auto *pRet = new(std::nothrow) CCNormalRule(); 
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

void CCNormalRule::setLevel(const int& level)
{
    if (nullptr == _gameScene->getPhysicsWorld())
    {
        CCLOGERROR("Scene is null");
    }
    _level = level;
    _gameScene->getPhysicsWorld()->setGravity(Point(0, -500*_level));
}

int CCNormalRule::getLevel()
{
    return _level;
}

bool CCNormalRule::isGameContinue(CCHeroAdapter &hero, CCSupportAdapter &support)
{
    if (0 == hero.getCurrentLive() )
    {
        if (CCAppConfig::getInstance()->getLevelScore(CCAppConfig::getInstance()->getLevelName())->asInt() <
            hero.getCurrentScore()
            )
        {
            CCAppConfig::getInstance()->setLevelScore(CCAppConfig::getInstance()->getLevelName(), 
                Value(hero.getCurrentScore()));
        }
        return false;
    }
    auto Score = hero.getCurrentScore();
    _storeUp += (support.getPropertyOfScore()>0?support.getPropertyOfScore():0);
    if (_storeUp > 2500)
    {
        auto level = _level;
        setLevel(++level);
        _storeUp = 0;
    }
    if (Score >= 21000)
    {
        gameOver();
    }
    return true;
}

void CCNormalRule::pauseAllRole()
{
    if (!_pauseAllRole)
    {
        getScheduler()->performFunctionInCocosThread([=](){
            _gameScene->getPhysicsWorld()->setGravity(Point::ZERO);
            auto Roles = _UIAdapter->getRole();
            for (auto role : Roles)
            {
                //同时碰撞，第二个不消失,需要放主线程运行
                role->pause();
                role->retain();
            }
            _gameScene->pause();
            _level==0?_level:_levelResume = _level;
            setLevel(0);
        });
        _pauseAllRole = true;
    }

}

void CCNormalRule::resumeAllRole()
{
    if (_pauseAllRole)
    {
        getScheduler()->performFunctionInCocosThread([=](){
        _gameScene->resume();
        auto Roles = _UIAdapter->getRole();
        for (auto role : Roles)
        {
            role->resume();
            role->release();
        }
        setLevel(_levelResume);
        _levelResume = 0;
    });
        _pauseAllRole = false;
    }
}

bool CCNormalRule::useObject(const std::string& Object)
{
    if ("fan" == Object)
    {
        auto fan = CCAppConfig::getInstance()->getObjectFan()-1;
        if (fan >= 0)
        {
            _UIAdapter->hideHaze();
            CCAppConfig::getInstance()->setObjectFan(fan);
            return true;
        }
    }
    return false;
}
