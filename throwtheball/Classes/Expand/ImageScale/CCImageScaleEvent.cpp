#include "CCImageScaleEvent.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;

CCImageScaleEvent::CCImageScaleEvent():
    _target(nullptr),
    _listenNode(nullptr),
    _isMove(false),
    _DistOld(0.0f),
    _DistNew(0.0f)
{
}

CCImageScaleEvent::~CCImageScaleEvent()
{

}

bool CCImageScaleEvent::init()
{
    if (!EventListenerTouchAllAtOnce::init())
    {
        return false;
    }
    EventListenerTouchAllAtOnce::onTouchesBegan      = CC_CALLBACK_2(CCImageScaleEvent::onTouchBegan, this);
    EventListenerTouchAllAtOnce::onTouchesMoved      = CC_CALLBACK_2(CCImageScaleEvent::onTouchMoved, this);
    EventListenerTouchAllAtOnce::onTouchesEnded      = CC_CALLBACK_2(CCImageScaleEvent::onTouchEnded, this);
    EventListenerTouchAllAtOnce::onTouchesCancelled  = CC_CALLBACK_2(CCImageScaleEvent::onTouchCancelled, this);
    //setSwallowTouches(true);
    return true;
}

CCImageScaleEvent* CCImageScaleEvent::clone()
{
    auto ret = new (std::nothrow) CCImageScaleEvent();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void CCImageScaleEvent::onTouchBegan(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event)
{
    if (nullptr != _listenNode)
    {
        if (touchs.size() == 1)
        {
            CCLOG("Image Began");

            auto locationInNode = _listenNode->convertToNodeSpace(touchs.front()->getLocation());
            auto s = _listenNode->getContentSize();
            auto rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode))
            {
                _isMove = true;
                return;
            }
            _isMove = false;
        }
        else
        {
            _isMove = false;
        }
    }
}

void CCImageScaleEvent::onTouchMoved(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event)
{
    if (nullptr != _target)
    {
        if (touchs.size() == 1 && _isMove)
        {
            Point offset = touchs[0]->getLocation() - touchs[0]->getPreviousLocation();
            _target->setPosition(_target->getPosition()+offset);
        }
        else if (touchs.size() > 1)
        {
            auto first = touchs[0]->getLocation();
            auto second = touchs[1]->getLocation();
            auto firstStart = touchs[0]->getPreviousLocation();
            auto secondStart = touchs[1]->getPreviousLocation();
            auto change = first.getDistance(second) - firstStart.getDistance(secondStart);
            change *= 0.5;
            _DistOld = _DistOld != 0.0f?_DistOld:firstStart.getDistance(secondStart);
            _DistNew = _DistNew != 0.0f?(change + _DistNew):first.getDistance(second);

            auto scale = (_DistNew/_DistOld);
            if (scale < 0.01f)
            {
                scale = 0.01f;
            }
            CCLOG("_DistOld:%f _DistNew:%f change:%f scale:%f", _DistOld, _DistNew, change, scale);
            _target->setScale(scale);
        }
    }
}

void CCImageScaleEvent::onTouchEnded(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event)
{
}

void CCImageScaleEvent::onTouchCancelled(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event)
{

}
