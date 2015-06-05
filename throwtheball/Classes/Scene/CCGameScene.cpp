#include "CCGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Rule/CCNormalRule.h"
#include "ui/UITextBMFont.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "Rule/CCLimitedRule.h"
#include "Audio/CCAudioHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;

CCGameScene::CCGameScene():
    _pauseLayer(nullptr), 
    _rootNode(nullptr),
    _pauseLayerShow(false),
    _gameOverLayer(nullptr),
    _gameOverLayerShow(false),
    _toastShow(false),
    _hazeShow(false),
    _redTime(false)
{                             
    CCLOG("CCGameScene create");
}
CCGameScene::~CCGameScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_pauseLayer);
    CC_SAFE_RELEASE_NULL(_gameOverLayer);
    CCLOG("CCGameScene delete");
}

// on "init" you need to initialize your instance
bool CCGameScene::init()
{
    CCLOG("CCGameScene init");
    if (!Scene::initWithPhysics()||
        !initRoot() ||
        !initPuaseLayer() ||
        !initGameOverLayer() )
    {
        CCLOGERROR("initWithPhysics faild");
        return false;
    }
    CCLOG("CCGameScene init ok");
    if (CCAppConfig::getInstance()->getIsLimited())
    {
        addChild(CCLimitedRule::create(dynamic_cast<CCGameUIAdapter *>(this)));
    }
    else
    {
        addChild(CCNormalRule::create(dynamic_cast<CCGameUIAdapter *>(this)));
    }
    setName("CCGameScene");
    return true;
}

bool CCGameScene::initPuaseLayer()
{
    CCLOG("initPuaseLayer init");
    _pauseLayer = CSLoader::createNode("Layer/Game/Pop/pause.csb");
    if (nullptr == _pauseLayer)
    {
        CCLOGERROR("Layer/Game/Pop/pause.csb load error");
        return false;
    }
    _pauseLayer->retain();
    auto listenter = CCSpriteButtomEvent::create();
    listenter->onClick = CC_CALLBACK_1(CCGameScene::buttonCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter,_pauseLayer->getChildByName("back"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter->clone(),_pauseLayer->getChildByName("level"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter->clone(),_pauseLayer->getChildByName("replay"));
    return true;
}

bool CCGameScene::initGameOverLayer()
{
    CCLOG("initGameOverLayer init");
    _gameOverLayer = CSLoader::createNode("Layer/Game/Pop/gameover.csb");
    if (nullptr == _gameOverLayer)
    {
        CCLOGERROR("Layer/Game/Pop/gameOver.csb load error");
        return false;
    }
    _gameOverLayer->retain();
    auto button= _gameOverLayer->getChildByName("marry");
    auto listen = CCSpriteButtomEvent::create();
    listen->onClick = CC_CALLBACK_1(CCGameScene::gameOverCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        listen, 
        _gameOverLayer->getChildByName("marry"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        listen->clone(), 
        _gameOverLayer->getChildByName("level"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        listen->clone(), 
        _gameOverLayer->getChildByName("replay"));
    return true;
}

bool CCGameScene::initRoot()
{
    CCLOG("initRoot init");
    _rootNode = CSLoader::createNode("Layer/Game/gameLayer.csb");
    if (nullptr == _rootNode)
    {
        CCLOGERROR("Layer/Game/Pop/gameOver.csb load error");
        return false;
    }
    _rootNode->retain();
    _rootNode->setName("wall");
    Size visibleSize = _rootNode->getContentSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.0F), 3.0f);
    body->setCategoryBitmask(1);
    body->setContactTestBitmask(2);
    body->setCollisionBitmask(5);
    _rootNode->setPhysicsBody(body);
    //_physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    _rootNode->setPosition(getContentSize().width/2, getContentSize().height/2);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCGameScene::puase, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _rootNode->getChildByName("tilte")->getChildByName("tools"));
    initObject();
    changeBackground();
    auto hydrangea = _rootNode->getChildByName<Sprite*>("hydrangea");
    auto touchEvent = EventListenerTouchOneByOne::create();
    touchEvent->setSwallowTouches(true);
    touchEvent->onTouchBegan = CC_CALLBACK_2(CCGameScene::onHydrangeaTouchBegan, this);
    touchEvent->onTouchMoved = CC_CALLBACK_2(CCGameScene::onHydrangeaTouchMove, this);
    hydrangea->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, hydrangea);

    addChild(_rootNode);
    return true;
}

void CCGameScene::initObject()
{
    char num[20] = {0};
    auto listener = CCSpriteButtomEvent::create();
    listener->setPressScale(1.0f);
    listener->onClick = CC_CALLBACK_1(CCGameScene::useObject, this);
    auto object = _rootNode->getChildByName("tilte")->getChildByName("fan");
    sprintf(num, "x%d", CCAppConfig::getInstance()->getObjectFan());
    object->getChildByName<ui::TextBMFont*>("num")->setString(num);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,object);
    object = _rootNode->getChildByName("tilte")->getChildByName("clock");
    sprintf(num, "x%d", CCAppConfig::getInstance()->getObjectClock());
    object->getChildByName<ui::TextBMFont*>("num")->setString(num);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),object);
}

void CCGameScene::changeBackground()
{
    if (CCAppConfig::getInstance()->getLevelName() == "waiter")
    {
        _rootNode->getChildByName<ui::ImageView*>("background")->loadTexture("Layer/Game/scene1.jpg");
    }
    else if (CCAppConfig::getInstance()->getLevelName() == "scholar")
    {
        _rootNode->getChildByName<ui::ImageView*>("background")->loadTexture("Layer/Game/scene2.jpg");
    }
    else if (CCAppConfig::getInstance()->getLevelName() == "general")
    {
        _rootNode->getChildByName<ui::ImageView*>("background")->loadTexture("Layer/Game/scene3.jpg");
    }
    else if (CCAppConfig::getInstance()->getLevelName() == "cateran")
    {
        _rootNode->getChildByName<ui::ImageView*>("background")->loadTexture("Layer/Game/scene4.jpg");
    }
    CCAudioHelper::getInstance()->playMusic(CCAppConfig::getInstance()->getLevelName());
}

void CCGameScene::onEnter()
{
    Scene::onEnter();
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gameStart();
}

void CCGameScene::onExit()
{
    Scene::onExit();
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gameOver();
    CCAudioHelper::getInstance()->playMusic("normal");
}

void CCGameScene::updateHeroScoreAndLive(const int& Hero, const int& score)
{
    char temp[64] = {0};
    sprintf(temp, "%d", score);
    (_rootNode->getChildByName("tilte")->getChildByName<ui::TextBMFont*>("score"))->setString(temp);
    CCAppConfig::getInstance()->setCurrentScore(score);
    sprintf(temp, "X %d", Hero);
    (_rootNode->getChildByName("tilte")->getChildByName("lives")->getChildByName<ui::TextBMFont*>("num"))->setString(temp);
}

void CCGameScene::addRole(cocos2d::Node* Role)
{
    _rootNode->getChildByName("background")->addChild(Role);
}

void CCGameScene::removeAllRole()
{
    _rootNode->getChildByName("background")->removeAllChildren();
}
cocos2d::Scene* CCGameScene::getGameScene()
{
    return this;
}

void CCGameScene::showPauseUI()
{
    if (!_pauseLayerShow)
    {
        addChild(_pauseLayer);
        _pauseLayerShow = true;
    }
}

void CCGameScene::hidePauseUI()
{
    if (_pauseLayerShow)
    {
        removeChild(_pauseLayer);
        _pauseLayerShow = false;
    }
}

Vector<cocos2d::Node*>& CCGameScene::getRole()
{
    return _rootNode->getChildByName("background")->getChildren();
}

void CCGameScene::puase(cocos2d::Node*)
{
    CCAudioHelper::getInstance()->playEffect(1);
    dynamic_cast<CCRule *>(getChildByName("Rule"))->gamePause();
}

void CCGameScene::showGameOverUI(const int &score)
{
    //score
    if (!_gameOverLayerShow)
    {
        auto scoreLabel = dynamic_cast<ui::TextBMFont*>(_gameOverLayer->getChildByName("score"));
        if (nullptr != scoreLabel &&
            nullptr != _gameOverLayer)
        {
            char Temp[20] = {0};
            sprintf(Temp, "%d", score);
            scoreLabel->setString(std::string(Temp) + 
                static_cast<cocostudio::ObjectExtensionData*>(scoreLabel->getUserObject()
                )->getCustomProperty());
            _rootNode->getChildByName("hydrangea")->setVisible(true);
            hideHaze();
            if (score > CCAppConfig::getInstance()->getLevelScore(
                CCAppConfig::getInstance()->getLevelName())->asInt())
            {
                CCAppConfig::getInstance()->setLevelScore(CCAppConfig::getInstance()->getLevelName(),
                    Value(score));
                //显示历史最高分
            }
        }
    }
}

void CCGameScene::hideGameOverUI()
{
    if (_gameOverLayerShow)
    {
        if (nullptr != _gameOverLayer)
        {
            _rootNode->getChildByName("hydrangea")->setPosition(360.0f, 580.0f);
            _rootNode->getChildByName("hydrangea")->setVisible(false);
            removeChild(_gameOverLayer);
            _gameOverLayerShow = false;
        }
    }
}

void CCGameScene::buttonCallback(Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    CCAudioHelper::getInstance()->playEffect(1);
    if ("back" == target->getName())
    {
        dynamic_cast<CCRule *>(getChildByName("Rule"))->gameResume();
    }
    else if ("level" == target->getName())
    {
        Director::getInstance()->popScene();
    }
    else if ("replay" == target->getName())
    {
        dynamic_cast<CCRule *>(getChildByName("Rule"))->gameRestart();
    }
}

void CCGameScene::gameOverCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    CCAudioHelper::getInstance()->playEffect(1);
    if ("level" == target->getName())
    {
        Director::getInstance()->popScene();
    }
    else if ("marry" == target->getName())
    {
        CCAppConfig::getInstance()->setShowMarry(true);
        Director::getInstance()->popScene();
    }
    else if ("replay" == target->getName())
    {
        dynamic_cast<CCRule *>(getChildByName("Rule"))->gameRestart();
    }
}

bool CCGameScene::onHydrangeaTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto hydrangea = dynamic_cast<Sprite*>(event->getCurrentTarget());
    auto point = touch->getLocation();
    if (nullptr == hydrangea || 
        !hydrangea->getBoundingBox().containsPoint(point))
    {
        return false;
    }
    return true;
}

void CCGameScene::onHydrangeaTouchMove(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto hydrangea = dynamic_cast<Sprite*>(event->getCurrentTarget());
    if (hydrangea->getPositionY() > touch->getLocation().y)
    {
        return ;
    }
    hydrangea->setPositionY(touch->getLocation().y);
    if (hydrangea->getPositionY() > 620 && !_gameOverLayerShow)
    {
        _gameOverLayerShow = true;
        _rootNode->getChildByName<Sprite*>("hydrangea")->setVisible(false);
        CCAppConfig::getInstance()->setLevelIsUnlock("scholar", Value(true));
        addChild(_gameOverLayer);
    }
}

void CCGameScene::showHaze()
{
    if (!_hazeShow)
    {
        CCAudioHelper::getInstance()->playEffect(15);
        _hazeShow = true;
//         _rootNode->getChildByName("haze_1")->runAction(
//             Sequence::createWithTwoActions(FadeIn::create(3.0f),
//             CallFunc::create(CC_CALLBACK_0(CCGameScene::showHaze2, this))));
        _rootNode->getChildByName("haze")->runAction(Sequence::create(FadeIn::create(6.0f),
            FadeOut::create(6.0f), CallFunc::create([=](void){
                _hazeShow = false;
        }), nullptr));
    }
}

void CCGameScene::showHaze2()
{
    _rootNode->getChildByName("haze_2")->runAction(
        Sequence::createWithTwoActions(FadeIn::create(3.0f),
        CallFunc::create([=](void){
            _rootNode->getChildByName("haze_2")->runAction(
                Sequence::createWithTwoActions(FadeOut::create(3.0f),
                CallFunc::create([=](void){
                    _rootNode->getChildByName("haze_1")->runAction(
                        Sequence::createWithTwoActions(FadeOut::create(3.0f),
                        CallFunc::create([=](void){
                            _hazeShow = false;
                    })));
            })));
    })));
}

void CCGameScene::hideHaze()
{
    if (_hazeShow)
    {
        _hazeShow = false;
//         _rootNode->getChildByName("haze_1")->stopAllActions();
//         _rootNode->getChildByName("haze_2")->stopAllActions();
//         _rootNode->getChildByName("haze_1")->runAction(FadeOut::create(0.1f));
//         _rootNode->getChildByName("haze_2")->runAction(FadeOut::create(0.1f));
        _rootNode->getChildByName("haze")->stopAllActions();
        _rootNode->getChildByName("haze")->runAction(FadeOut::create(0.1f));
    }
}

void CCGameScene::showToast()
{
    if (!_toastShow)
    {
        _rootNode->getChildByName("toast")->runAction(
            Sequence::createWithTwoActions(FadeIn::create(0.5f),
            CallFunc::create(CC_CALLBACK_0(CCGameScene::hideToast, this))));
        _toastShow = true;
    }
}

void CCGameScene::hideToast()
{
    if (_toastShow)
    {
        _rootNode->getChildByName("toast")->runAction(FadeOut::create(1.0f));
        _toastShow = false;
    }
}

void CCGameScene::useObject(cocos2d::Node* target)
{
    if (_rootNode->getChildByName("hydrangea")->isVisible())
    {
        return ;
    }
    if (nullptr != target)
    {
        if ("fan" == target->getName() /*&& _hazeShow*/)
        {
            if (dynamic_cast<CCRule *>(getChildByName("Rule"))->useObject("fan"))
            {
                CCAudioHelper::getInstance()->playEffect(6);
                char Temp[20] = {0};
                sprintf(Temp, "x%d", CCAppConfig::getInstance()->getObjectFan());
                target->getChildByName<ui::TextBMFont*>("num")->setString(Temp);
            }
            else if (_hazeShow)
            {
                CCAudioHelper::getInstance()->playEffect(12);
                showToast();
            }
        }
        else if ("clock" == target->getName())
        {
            if (dynamic_cast<CCRule *>(getChildByName("Rule"))->useObject("clock"))
            {
                CCAudioHelper::getInstance()->playEffect(7);
                char Temp[20] = {0};
                sprintf(Temp, "x%d", CCAppConfig::getInstance()->getObjectClock());
                target->getChildByName<ui::TextBMFont*>("num")->setString(Temp);
            }
            else
            {
                CCAudioHelper::getInstance()->playEffect(12);
                showToast();
            }
        }
    }

}

void CCGameScene::setlimited(bool set)
{
    if (set)
    {
        _rootNode->getChildByName("tilte")->getChildByName("lives")->setVisible(false);
        _rootNode->getChildByName("tilte")->getChildByName("time")->setVisible(true);
        _rootNode->getChildByName("tilte")->getChildByName("clock")->setVisible(true);
    }
    else
    {
        _rootNode->getChildByName("tilte")->getChildByName("lives")->setVisible(true);
        _rootNode->getChildByName("tilte")->getChildByName("clock")->setVisible(false);
        _rootNode->getChildByName("tilte")->getChildByName("time")->setVisible(false);
    }
}

void CCGameScene::updateTime(const int& time)
{
    std::stringstream s;
    s << time;
    auto timeNode =_rootNode->getChildByName("tilte")->getChildByName<ui::TextBMFont*>("time");
    timeNode->setString(s.str());
    if (time <= 5 && time > 0)
    {
        CCAudioHelper::getInstance()->playEffect(12);
        timeNode->setColor(Color3B(0xff, 0, 0));
        timeNode->runAction(Sequence::createWithTwoActions(
            ScaleTo::create(0.5f, 2.5f),
            ScaleTo::create(0.5f, 1.8f)));
        _redTime = true;
    }
    else if (_redTime)
    {
        timeNode->setColor(Color3B(0x40, 0x24, 0x07));
        timeNode->setScale(1.8f);
        _redTime = false;
    }
}

