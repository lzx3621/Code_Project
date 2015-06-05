#include "CCSelectLevelLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "CCStoreLayer.h"
#include "Scene/CCMenuScene.h"
#include "CCPhotoLayer.h"
#include "CCHeadShotLayer.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCSelectLevelLayer::CCSelectLevelLayer()
    :_rootNode(nullptr),
    _option(nullptr),
    _bride(0),
    _isUnLock(nullptr)
{
    CCLOG("CCSelectLevelLayer create");
}

CCSelectLevelLayer::~CCSelectLevelLayer()
{
    CC_SAFE_RELEASE_NULL(_option);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CC_SAFE_RELEASE_NULL(_isUnLock);
    CCLOG("CCSelectLevelLayer delete");
}

bool CCSelectLevelLayer::init()
{
    _rootNode   = CSLoader::createNode("Layer/Level/selectLevel.csb");
    if (!Layer::init() ||
        nullptr == _rootNode ||
        !initOption() ||
        !initIsLock())
    {
        return false;
    }
    setName("CCSelectLevelLayer");
    initLevelSelect();
    _rootNode->retain();
    addChild(_rootNode);
    return true;
}

bool CCSelectLevelLayer::initIsLock()
{
    _isUnLock = CSLoader::createNode("Layer/Level/Unlock/unlock.csb");
    if (_isUnLock == nullptr)
    {
        return false;
    }
    CC_SAFE_RETAIN(_isUnLock);
    auto event = CCSpriteButtomEvent::create();
    event->onClick = CC_CALLBACK_1(CCSelectLevelLayer::onIsUnLockCallback,this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        event,
        _isUnLock->getChildByName("back"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        event->clone(),
        _isUnLock->getChildByName("unLock"));
    return true;
}
bool CCSelectLevelLayer::initOption()
{
    _option = _rootNode->getChildByName("option");
    if (nullptr == _option ||
        !initButtom())
    {
        CCLOGERROR("Layer/Load/loading.csb load failed!");
        return false;
    }
    _option->retain();
    return true;
}

void CCSelectLevelLayer::initLevelSelect()
{
    auto checkBoxes = _option->getChildByName<ui::Layout*>("checkGroup")->getChildren();
    ui::CheckBox* Temp = nullptr;
    auto i(0);
    for (auto& checkBox : checkBoxes)
    {
        Temp = dynamic_cast<ui::CheckBox*>(checkBox);
        if (nullptr != Temp)
        {
            Temp->addEventListener(CC_CALLBACK_2(CCSelectLevelLayer::selectedStateEvent, this));
            auto enable = CCAppConfig::getInstance()->getLevelIsUnlock(checkBox->getName())->asBool();
            setCheckBoxEnable(Temp, enable);
            if (!enable)
            {
                auto listen = CCSpriteButtomEvent::create();
                listen->setPressScale(1.0);
                listen->onClick = CC_CALLBACK_1(CCSelectLevelLayer::onUnlockCallback, this);
                _listeners[Temp->getName()] = listen;
                getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, Temp);
            }
            else
            {
                _listeners[Temp->getName()] = nullptr;
            }

            if (Temp->getName() == CCAppConfig::getInstance()->getLevelName())
            {
                Temp->setSelected(true);
            }
            else
            {
                Temp->setSelected(false);
            }
        }
        i++;
    }
}


bool CCSelectLevelLayer::initButtom()
{
    auto sprite = _option->getChildByName("limited");
    if (nullptr == sprite)
    {
        CCLOGERROR("Limited load failed!");
        return false;
    }
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCSelectLevelLayer::onOpitonCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
    sprite = _option->getChildByName("normal");
    if (nullptr == sprite)
    {
        CCLOGERROR("normal load failed!");
        return false;
    }
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
    sprite = _option->getChildByName("store");
    if (nullptr == sprite)
    {
        CCLOGERROR("store load failed!");
        return false;
    }
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
    sprite = _option->getChildByName("back");
    if (nullptr == sprite)
    {
        CCLOGERROR("back load failed!");
        return false;
    }
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
    sprite = _option->getChildByName("photo");
    if (nullptr == sprite)
    {
        CCLOGERROR("photo load failed!");
        return false;
    }
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
    return true;
}

void CCSelectLevelLayer::selectedStateEvent(Ref* pSender, ui::CheckBox::EventType type)
{
    switch (type)
    {
    case ui::CheckBox::EventType::UNSELECTED:
        {
            //保证至少有一个被选
            auto checkBoxes = _option->getChildByName<ui::Layout*>("checkGroup")->getChildren();
            bool check = false;
            ui::CheckBox* temp = nullptr;
            for (auto checkBox : checkBoxes)
            {
                temp = dynamic_cast<ui::CheckBox*>(checkBox);
                if (temp && temp->isSelected())
                {
                    check = true;
                }
            }
            if (!check)
            {
                if (ui::CheckBox* temp = dynamic_cast<ui::CheckBox*>(pSender))
                {
                    temp->setSelected(true);
                }
            }
        }
        break;

    case ui::CheckBox::EventType::SELECTED:
        {
            auto checkBoxes = _option->getChildByName<ui::Layout*>("checkGroup")->getChildren();
            ui::CheckBox* Temp = nullptr;
            for (auto checkBox : checkBoxes)
            {
                Temp = dynamic_cast<ui::CheckBox*>(checkBox);
                if (nullptr != Temp && Temp != pSender)
                {
                    Temp->setSelected(false);
                }
            }
            CCAudioHelper::getInstance()->playEffect(16);
            CCAppConfig::getInstance()->setLevelName(dynamic_cast<ui::CheckBox*>(pSender)->getName());
            CCLOG("%s Selected", dynamic_cast<ui::CheckBox*>(pSender)->getName().c_str());
        }
        break;

    default:
        break;
    }
}

void CCSelectLevelLayer::setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable)
{
    if (nullptr != cbox)
    {
        cbox->setEnabled(enable);
        if (enable)
        {
            cbox->getChildByName("title")->setVisible(true);
            cbox->getChildByName("disable")->setVisible(false);
        }
        else
        {
            cbox->getChildByName("title")->setVisible(false);
            cbox->getChildByName("disable")->setVisible(true);
        }
    }
}


void CCSelectLevelLayer::onOpitonCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());

    CCAudioHelper::getInstance()->playEffect(1);
    if ("limited" == target->getName())
    {
        CCAppConfig::getInstance()->setIsLimited(true);
        getParent()->addChild(CCHeadShotLayer::create());
    }
    else if ("normal" == target->getName())
    {
        CCAppConfig::getInstance()->setIsLimited(false);
        getParent()->addChild(CCHeadShotLayer::create());
    }
    else if ("back" == target->getName())
    {
        Director::getInstance()->end();
    }
    else if ("store" == target->getName())
    {
        getParent()->addChild(CCStoreLayer::create());
    }
    else if ("photo" == target->getName())
    {
        getParent()->addChild(CCPhotoLayer::create());
        target->getChildByName("new")->setVisible(true);
    }
}

void CCSelectLevelLayer::onUnlockCallback(cocos2d::Node* target)
{
    CCLOG("onUnlockCallback %s", target->getName().c_str());
    if (!target->getChildByName("disable")->isVisible())
    {
        //已经解锁着返回
        return ;
    }
    else
    {
        CCAudioHelper::getInstance()->playEffect(11);
        _UnLockName = target->getName();
        _isUnLock->getChildByName("notenough")->setVisible(false);
        if ("cateran" == _UnLockName)
        {
            _isUnLock->getChildByName("unlock_1")->setVisible(true);
            _isUnLock->getChildByName("unlock_2")->setVisible(false);
            _UnLockMoney = 1000;
            addChild(_isUnLock);
        }
        else if("general" == _UnLockName)
        {
            _UnLockMoney = 1500;
            _isUnLock->getChildByName("unlock_2")->setVisible(true);
            _isUnLock->getChildByName("unlock_1")->setVisible(false);
            addChild(_isUnLock);
        }
    }
    //弹框，问是不是要花钱解锁
}

void CCSelectLevelLayer::onEnter()
{
    Layer::onEnter();
    if (nullptr != _option)
    {
        if (CCAppConfig::getInstance()->getNewBride())
        {
            _option->getChildByName("photo")->getChildByName("new")->setVisible(true);
        }
        else
        {
            _option->getChildByName("photo")->getChildByName("new")->setVisible(false);
        }
        updateUnList();
    }
}

void CCSelectLevelLayer::onIsUnLockCallback(cocos2d::Node* target)
{
    if ("unLock" == target->getName())
    {
        auto money = CCAppConfig::getInstance()->getMoney();
        if (money > _UnLockMoney)
        {
            CCLOG("UnLockName:%s",_UnLockName.c_str());
            CCAppConfig::getInstance()->setLevelIsUnlock(_UnLockName, Value(true));
            CCAppConfig::getInstance()->setMoney(money-_UnLockMoney);
            removeChild(_isUnLock);
            updateUnList();
        }
        else
        {
            _isUnLock->getChildByName("unlock_1")->setVisible(false);
            _isUnLock->getChildByName("unlock_2")->setVisible(false);
            _isUnLock->getChildByName("notenough")->setVisible(true);
        }
    }
    else if ("back" == target->getName())
    {
        removeChild(_isUnLock);
    }
}

void CCSelectLevelLayer::updateUnList()
{
    auto items = _option->getChildByName<ui::Layout*>("checkGroup")->getChildren();
    auto i(0), max(0) ,score(0);
    Node* iterMax = nullptr;
    for (auto &item:items)
    {
        if (CCAppConfig::getInstance()->getLevelIsUnlock(item->getName())->asBool()
            && item->getChildByName("disable")->isVisible()
            && nullptr != _listeners[item->getName()])
        {
            CCLOG("%s Unlock", item->getName().c_str());
            getEventDispatcher()->removeEventListener(_listeners[item->getName()]);
            _listeners[item->getName()] = nullptr;
            static_cast<ui::CheckBox*>(item)->addEventListener(CC_CALLBACK_2(CCSelectLevelLayer::selectedStateEvent, this));
            setCheckBoxEnable(static_cast<ui::CheckBox*>(item), true);
        }
        item->getChildByName("best")->setVisible(false);
        score = CCAppConfig::getInstance()->getLevelScore(item->getName())->asInt();
        if (max<score)
        {
            max = score;
            iterMax = item;
        }
        i++;
    }
    if (nullptr != iterMax)
    {
        iterMax->getChildByName("best")->setVisible(true);
    }

}

