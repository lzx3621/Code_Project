#include "CCNormalRule.h"
#include "CCRoleFactory.h"
#include "CCRoleAdapter.h"

USING_NS_CC;

void CCNormalRule::onStart()
{
    if (!_isStart)
    {
		schedule(CC_CALLBACK_1(CCNormalRule::createObjectOffFall, this),
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
			touchListener, hero);
		_gamescene = getScene();
		_isStart = true;
    }
    
}

void CCNormalRule::onRestat()
{

}

void CCNormalRule::onPause()
{

}

void CCNormalRule::onEnd()
{
	_gamescene = nullptr;
	_isStart = true;
}

void CCNormalRule::createObjectOffFall( float dt )
{
    if (nullptr == _roleFactory)
    {
        return ;
    }
    //(RoleType)cocos2d::random((int)DAMAGE_HYDRANGEA, (int)GAIN_JADE)
    //保证主线程执行
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
        auto role = _roleFactory->createRole((RoleType)cocos2d::random<int>((int)DAMAGE_HYDRANGEA, (int)GAIN_JADE));
        auto roleSize = role->getContentSize();
        auto apartLeftmin = roleSize.width/2;
        auto apartRightMax = _gamescene->getContentSize().width - (roleSize.width/2);
        auto height = _gamescene->getContentSize().height - (roleSize.height/2);
        role->setPosition(cocos2d::random<float>(apartLeftmin, apartRightMax), height-4);
    });
}

bool CCNormalRule::init()
{
    if (CCRule::init())
    {
        CCHeroAdapter::setHeroContactCallback(CC_CALLBACK_2(CCNormalRule::onHeroContact, this));
        CCSupportAdapter::setObjectContactBottomCallback(CC_CALLBACK_1(CCNormalRule::onObjectContactBottom,this));
        if (nullptr == _roleFactory)
        {
            _roleFactory = CCRoleFactory::create();
        }
		addChild(_roleFactory);

        return true;
    }
    else
    {
        return false;
    }
}

bool CCNormalRule::onHeroTouchBegan(Touch* touch, Event* event)
{
    /*event->*/
	auto hero		= event->getCurrentTarget();
	auto heroSize	= hero->getContentSize();
	//是否在精灵上的点击,并且没有超出边界,浮点数不要判断=了
	if (nullptr != _gamescene && 
        heroSize.height > touch->getLocation().y &&
		(heroSize.width)/2 > abs(hero->getPositionX() - touch->getLocation().x))
	{
        auto apartLeftmin = heroSize.width/2;
        auto apartRightMax = _gamescene->getContentSize().width - (heroSize.width/2);
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
    if (nullptr != _gamescene &&
        heroSize.height > touch->getLocation().y )
	{
        auto apartLeftmin = heroSize.width/2;
        auto apartRightMax = _gamescene->getContentSize().width - (heroSize.width/2);
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
            auto spriteParent   = sprite->getParent();
            spriteParent?spriteParent->removeChild(sprite):NULL;
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
