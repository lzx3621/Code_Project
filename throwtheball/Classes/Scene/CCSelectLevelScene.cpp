#include "CCSelectLevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCSelectLevelScene::CCSelectLevelScene()
    :_rootNode(nullptr),
    _CheckGroup(nullptr)
{

}

CCSelectLevelScene::~CCSelectLevelScene()
{
    CC_SAFE_RELEASE_NULL(_rootNode);
}

Scene* CCSelectLevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    if (nullptr != scene)
    {
        auto layer = CCSelectLevelScene::create();
        if (nullptr != layer)
        {
            scene->addChild(layer);
            return scene;
        }
    }
    return nullptr;
}

// on "init" you need to initialize your instance
bool CCSelectLevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _rootNode   = CSLoader::createNode("Scene/Level/SelectLevel.csb");
    if (!Scene::init() ||
        nullptr == _rootNode ||
        !initMenu() ||
        !initSelect())
    {
        return false;
    }
    setName("CCSelectLevelScene");
    _rootNode->retain();
    
    addChild(_rootNode);

    return true;
}

bool CCSelectLevelScene::initMenu()
{
    auto sprite = _rootNode->getChildByName("Limited");
    if (nullptr == sprite)
    {
        CCLOG("Limited load failed!");
        return false;
    }
    sprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(CCSpriteButtomEvent::create(), sprite);
    return true;
}

bool CCSelectLevelScene::initSelect()
{
    _CheckGroup = _rootNode->getChildByName<ui::Layout*>("CheckGroup");
    if (nullptr == _CheckGroup)
    {
        CCLOG("Scene/Load/loading.csb load failed!");
        return false;
    }
    auto checkBoxes = _CheckGroup->getChildren();
    ui::CheckBox* Temp = nullptr;
    for (auto checkBox : checkBoxes)
    {
        Temp = dynamic_cast<ui::CheckBox*>(checkBox);
        if (nullptr != Temp)
        {
            Temp->addEventListener(CC_CALLBACK_2(CCSelectLevelScene::selectedStateEvent, this));
            setCheckBoxEnable(Temp, false);
        }
    }
    return true;
}

void CCSelectLevelScene::selectedStateEvent(Ref* pSender, ui::CheckBox::EventType type)
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

void CCSelectLevelScene::setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable)
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

