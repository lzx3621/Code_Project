#include "CCNormalRule.h"
#include "./Role/CCRoleFactory.h"
#include "./Adapter/CCRoleAdapter.h"
#include "./Adapter/CCGameUIAdapter.h"

USING_NS_CC;

CCNormalRule::CCNormalRule():
    _isStart(false),
    _gameScene(nullptr),
    _UIAdapter(nullptr),
    _level(0),
    _storeUp(0),
    _levelResume(0)
{
}

CCNormalRule::~CCNormalRule(void)
{
    if (nullptr != _gameScene)
    {
       _gameScene->release();
    }
    _gameScene = nullptr;
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
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(CCNormalRule::onHeroTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(CCNormalRule::onHeroTouchMove, this);
		auto hero = _roleFactory->createRole(MAIN_HERO, Vec2(0,0));
        hero->setPosition(hero->getContentSize().width/2, (hero->getContentSize().height/2)+3);
		hero->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
			touchListener,hero);
        _UIAdapter->addRole(hero);
		_isStart = true;
    }
    
}

void CCNormalRule::gameRestart()
{

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
    _gameScene->unschedule(std::string("createObjectOffFall"));
    pauseAllRole();
	_isStart = true;
}

void CCNormalRule::createObjectOffFall( float dt )
{
    if (nullptr == _roleFactory)
    {
        return ;
    }
    for (auto i = 0, max = cocos2d::random<int>(1, 3);
        i < max;
        i++)
    {
        addRole((RoleType)cocos2d::random<int>((int)DAMAGE_TILE, (int)GAIN_JADE));
    }
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
        return false;
    }
    _gameScene = _UIAdapter->getGameScene();
    _gameScene->retain();
    setName("Rule");
    CCHeroAdapter::setHeroContactCallback(CC_CALLBACK_2(CCNormalRule::onHeroContact, this));
    CCSupportAdapter::setObjectContactBottomCallback(CC_CALLBACK_1(CCNormalRule::onObjectContactBottom,this));

    addChild(_roleFactory);
    setLevel(1);
    return true;
}

bool CCNormalRule::onHeroTouchBegan(Touch* touch, Event* event)
{
	auto hero		= event->getCurrentTarget();
    if (hero == nullptr || "Hero" != hero->getName())
    {
        return true;
    }
	auto heroSize	= hero->getContentSize();
	//是否在精灵上的点击,并且没有超出边界,浮点数不要判断=了
	if (nullptr != _gameScene && 
        0 == _levelResume &&
        heroSize.height > touch->getLocation().y &&
		(heroSize.width)/2 > abs(hero->getPositionX() - touch->getLocation().x))
	{
        auto apartLeftmin = heroSize.width/2;
        auto apartRightMax = _gameScene->getContentSize().width - (heroSize.width/2);
        if ((apartLeftmin > touch->getLocation().x))
        {
            hero->setPositionX(apartLeftmin);
        }
        else if (apartRightMax < touch->getLocation().x)
        {
            hero->setPositionX(apartRightMax);
        }
        else
        {
		    hero->setPositionX(touch->getLocation().x);
        }
		return true;
	}
	else
	{
		return false;
	}
}

void CCNormalRule::onHeroTouchMove(Touch* touch, Event* event)
{
    auto hero		= event->getCurrentTarget();
	auto heroSize	= event->getCurrentTarget()->getContentSize();
    if (nullptr != _gameScene &&
        0 == _levelResume &&
        heroSize.height > touch->getLocation().y )
	{
        auto apartLeftmin = heroSize.width/2;
        auto apartRightMax = _gameScene->getContentSize().width - (heroSize.width/2);
        if ((apartLeftmin > touch->getLocation().x))
        {
            hero->setPositionX(apartLeftmin);
        }
        else if (apartRightMax < touch->getLocation().x)
        {
            hero->setPositionX(apartRightMax);
        }
        else
        {
            hero->setPositionX(touch->getLocation().x);
        }
	}
};

void CCNormalRule::onHeroContact(CCHeroAdapter* hero, CCSupportAdapter* support)
{
    if (nullptr != support)
    {
        auto sprite = support->getSprite();
        if (nullptr != sprite)
        {
            auto live = hero->getCurrentLive();
            auto score = hero->getCurrentScore();
            live += support->getPropertyOfLive();
            score += support->getPropertyOfScore();

            hero->setCurrentLive(live<0?live = 0:live);
            hero->setCurrentScore(score<0?score = 0:score);
            _UIAdapter->updateheroScoreAndLive(live, score);
            sprite->removeFromParent();
        }
    }
}

void CCNormalRule::onObjectContactBottom(CCSupportAdapter* support)
{
    if (nullptr != support)
    {
        auto sprite = support->getSprite();
        if (nullptr != sprite)
        {
            sprite->removeFromParent();
        }
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
        CCLOG("Scene is null");
    }
    _level = level;
    _gameScene->getPhysicsWorld()->setGravity(Vec2(0, -500*_level));
}

int CCNormalRule::getLevel()
{
    return _level;
}

bool CCNormalRule::gameContinue(CCHeroAdapter* &hero, CCSupportAdapter* &support)
{
    if (0 == hero->getCurrentLive())
    {
        return false;
    }
    auto Score = hero->getCurrentScore();
    _storeUp += (support->getPropertyOfScore()>0?support->getPropertyOfScore():0);
    if (_storeUp > 1750)
    {
        auto level = _level;
        setLevel(++level);
        _storeUp = 0;
    }
    if (Score >= 21000)
    {
        addRole(GAIN_HYDRANGEA);
    }
    
    return true;
}

void CCNormalRule::addRole(RoleType type)
{
    auto role = _roleFactory->createRole(type);
    if (nullptr == role)
    {
        CCLOG("can\'t not create role!");
        return ;
    }
    auto roleSize = role->getContentSize();
    auto apartLeftmin = roleSize.width/2;
    auto apartRightMax = _gameScene->getContentSize().width - (roleSize.width/2);
    auto height = _gameScene->getContentSize().height - (roleSize.height/2);
    role->setPosition(cocos2d::random<float>(apartLeftmin, apartRightMax), height-4);
    _UIAdapter->addRole(role);
}

void CCNormalRule::pauseAllRole()
{
    _gameScene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    auto Roles = _UIAdapter->getRole();
    for (auto role : Roles)
    {
//         role->pause();
//         role->retain();
        _velocity.insert(std::make_pair(static_cast<Sprite*>(role),
            role->getPhysicsBody()->getVelocity()));
        role->getPhysicsBody()->setVelocity(Vec2::ZERO);
    }
    _gameScene->pause();
    _level==0?_level:_levelResume = _level;
    setLevel(0);
}

void CCNormalRule::resumeAllRole()
{
    _gameScene->resume();
    auto Roles = _UIAdapter->getRole();
    for (auto role : Roles)
    {
//         role->resume();
//         role->release();
        role->getPhysicsBody()->setVelocity(_velocity.at(static_cast<Sprite*>(role)));
    }
    _velocity.clear();
    setLevel(_levelResume);
    _levelResume = 0;
}
