#include "CCSpriteButtom.h"
USING_NS_CC;


CCSpriteButtom::CCSpriteButtom():
    _Sprite(nullptr)
{

}

CCSpriteButtom::~CCSpriteButtom()
{

}

bool CCSpriteButtom::init()
{
    if(!Node::init()){
        return false;
    }
    return true;
}

bool CCSpriteButtom::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void CCSpriteButtom::onTouchMoved(Touch *touch, Event *event)
{

}

void CCSpriteButtom::onTouchEnded(Touch* touch, Event* event)
{

}

CCSpriteButtom* CCSpriteButtom::create(const char* backgroundImage, Size dialogSize)
{
    return nullptr;
}

void CCSpriteButtom::onEnter()
{
    Node::onEnter();
    _Sprite = dynamic_cast<Sprite*>(getParent());
    if(nullptr != _Sprite)
    {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan      = CC_CALLBACK_2(CCSpriteButtom::onTouchBegan, this);
        listener->onTouchMoved      = CC_CALLBACK_2(CCSpriteButtom::onTouchMoved, this);
        listener->onTouchEnded      = CC_CALLBACK_2(CCSpriteButtom::onTouchEnded, this);
        listener->onTouchCancelled  = CC_CALLBACK_2(CCSpriteButtom::onTouchCancelled, this);
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->addEventListenerWithSceneGraphPriority(listener, _Sprite);
    }
}

void CCSpriteButtom::onExit()
{

    Node::onExit();
}

void CCSpriteButtom::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event)
{

}

