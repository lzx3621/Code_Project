#include "CCStoreScene.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "PlayerConfig/CCAppConfig.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCStoreScene::CCStoreScene()
    :_rootNode(nullptr),
    _storeNode(nullptr)
{

}

CCStoreScene::~CCStoreScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
}

// on "init" you need to initialize your instance
bool CCStoreScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Scene/Store/store.csb");
    if (!Scene::init() ||
        nullptr == _rootNode ||
        !initStoreNode())
    {
        return false;
    }
    setName("CCStoreScene");
    _rootNode->retain();
    addChild(_rootNode);

    return true;
}


bool CCStoreScene::initStoreNode()
{
    _storeNode = _rootNode->getChildByName("StoreNode");
    if (nullptr == _storeNode)
    {
        CCLOG("Scene/Store/store.csb load failed!");
        return false;
    }

    auto pageView = _storeNode->getChildByName<ui::PageView*>("PageView");
    pageView->scrollToPage(0);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCStoreScene::onButtomCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_storeNode->getChildByName("back"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),_storeNode->getChildByName("ok"));

    pageView->addEventListener(CC_CALLBACK_2(CCStoreScene::PageViewCallback, this));
    auto checkBoxes = pageView->getChildByName<ui::Layout*>("page_2")->getChildren();
    ui::CheckBox* Temp = nullptr;
    auto i = 0;
    for (auto checkBox : checkBoxes)
    {
        Temp = dynamic_cast<ui::CheckBox*>(checkBox);
        if (nullptr != Temp)
        {
            Temp->addEventListener(CC_CALLBACK_2(CCStoreScene::selectedEvent, this));
        }
    }
    return true;
}

void CCStoreScene::selectedEvent(Ref* pSender, ui::CheckBox::EventType type)
{
    switch (type)
    {
    case ui::CheckBox::EventType::UNSELECTED:
        CCLOG("Unselected");
        break;

    case ui::CheckBox::EventType::SELECTED:
        CCLOG("Selected");
        break;

    default:
        break;
    }
}

void CCStoreScene::setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable)
{
    if (nullptr != cbox)
    {
        cbox->setEnabled(enable);
        std::string name = cbox->getName().substr(cbox->getName().find("_")+1, cbox->getName().length());

        if (enable)
        {
            cbox->getChildByName(name + "_title")->setVisible(true);
            cbox->getChildByName(name + "_disable")->setVisible(false);
        }
        else
        {
            cbox->getChildByName(name + "_title")->setVisible(false);
            cbox->getChildByName(name + "_disable")->setVisible(true);
        }
    }
}

void CCStoreScene::onButtomCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    if ("back" == target->getName())
    {

    }
    else if ("ok" == target->getName())
    {

    }
}

void CCStoreScene::PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event)
{
    auto curPageIndex = _storeNode->getChildByName<ui::PageView*>("PageView")->getCurPageIndex();
    CCLOG("CurPageIndex %d", curPageIndex);
    if (curPageIndex == 0)
    {
        //第一页
        _storeNode->getChildByName("direction_l_n")->setVisible(false);
        _storeNode->getChildByName("direction_r_n")->setVisible(true);
    }
    else if (curPageIndex == _storeNode->getChildByName<ui::PageView*>("PageView")->getChildrenCount()-1)
    {
        //最后一页
        _storeNode->getChildByName("direction_l_n")->setVisible(true);
        _storeNode->getChildByName("direction_r_n")->setVisible(false);
    }
    else
    {
        //中间
        _storeNode->getChildByName("direction_l_n")->setVisible(true);
        _storeNode->getChildByName("direction_r_n")->setVisible(true);
    }
}

