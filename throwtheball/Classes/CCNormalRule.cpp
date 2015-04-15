#include "CCNormalRule.h"
#include "CCRoleFactory.h"
#include "CCRoleAdapter.h"
#include "CCGameScene.h"

USING_NS_CC;

CCNormalRule::CCNormalRule(Node* gameScene):
    _isStart(false),
    _gameScene(nullptr)
{
    if (nullptr != gameScene)
    {
        _gameScene = gameScene;
        _gameScene->retain();
    }
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
			5.0f, 
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
        _gameScene->addChild(hero);
		_isStart = true;
    }
    
}

void CCNormalRule::gameRestart()
{

}

void CCNormalRule::gamePause()
{

}

void CCNormalRule::gameOver()
{
	_gameScene = nullptr;
	_isStart = true;
}

void CCNormalRule::createObjectOffFall( float dt )
{
    if (nullptr == _roleFactory)
    {
        return ;
    }

    auto role = _roleFactory->createRole((RoleType)cocos2d::random<int>((int)DAMAGE_HYDRANGEA, (int)GAIN_JADE));
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
    _gameScene->addChild(role);
}

bool CCNormalRule::init()
{
    _roleFactory = CCRoleFactory::create();
    if (nullptr == _gameScene || 
        nullptr == _roleFactory ||
        !Node::init())
    {
        return false;
    }
    setName("Rule");
    CCHeroAdapter::setHeroContactCallback(CC_CALLBACK_2(CCNormalRule::onHeroContact, this));
    CCSupportAdapter::setObjectContactBottomCallback(CC_CALLBACK_1(CCNormalRule::onObjectContactBottom,this));

    _gameScene->addChild(_roleFactory);

    return true;
}

bool CCNormalRule::onHeroTouchBegan(Touch* touch, Event* event)
{
	auto hero		= event->getCurrentTarget();
    if (hero == nullptr)
    {
        return true;
    }
	auto heroSize	= hero->getContentSize();
	//是否在精灵上的点击,并且没有超出边界,浮点数不要判断=了
	if (nullptr != _gameScene && 
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
            dynamic_cast<CCGameUIAdapter*>(_gameScene)->updateheroScoreAndLive(live, score);
            auto spriteParent   = sprite->getParent();
            spriteParent?spriteParent->removeChild(sprite):NULL;
            hero->setCurrentLive(live);
            hero->setCurrentScore(score);
            if (0 == live)
            {
                gameOver();
            }
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
            auto spriteParent   = sprite->getParent();
            spriteParent?spriteParent->removeChild(sprite):NULL;
        }
    }
}

CCNormalRule* CCNormalRule::create(cocos2d::Node* game)
{
    auto *pRet = new(std::nothrow) CCNormalRule(game); 
    if (pRet && pRet->init()) 
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
