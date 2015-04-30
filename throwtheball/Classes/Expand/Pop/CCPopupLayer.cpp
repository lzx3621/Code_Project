#include "CCPopupLayer.h"
USING_NS_CC;


CCPopupLayer::CCPopupLayer():
    m__pMenu(NULL)
    , m_contentPadding(0)
    , m_contentPaddingTop(0)
    , m_callbackListener(NULL)
    , m_callback(NULL)
    , m__sfBackGround(NULL)
    , m__s9BackGround(NULL)
    , m__ltContentText(NULL)
    , m__ltTitle(NULL)
{

}

CCPopupLayer::~CCPopupLayer()
{
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

bool CCPopupLayer::init()
{
    if(!LayerColor::init()){
        return false;
    }
    // 初始化需要的 Menu
    Menu* menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    setMenuButton(menu);

    //add layer touch event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CCPopupLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CCPopupLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CCPopupLayer::onTouchEnded, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    setColor(Color3B(0,0,0));  
    setOpacity(128);  

    return true;
}

bool CCPopupLayer::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void CCPopupLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void CCPopupLayer::onTouchEnded(Touch* touch, Event* event)
{

}

CCPopupLayer* CCPopupLayer::create(const char* backgroundImage, Size dialogSize)
{
    CCPopupLayer* layer = CCPopupLayer::create();
    //	layer->setSpriteBackGround(Sprite::create(backgroundImage));
    layer->setSprite9BackGround(ui::ImageView::create(backgroundImage));

    layer->m_dialogContentSize = dialogSize;

    return layer;
}

void CCPopupLayer::setTitle(const char* title, int fontsize /* = 20 */)
{
    Label* label = Label::createWithTTF(title,"",fontsize);
    setLabelTitle(label);
}

void CCPopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
    Label* ltf = Label::createWithTTF(text, "", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}

void CCPopupLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;    
}

bool CCPopupLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */)
{

    auto size = Director::getInstance()->getWinSize();
    auto center = Point(size.width / 2, size.height / 2);

    // 创建图片菜单按钮
    auto item = MenuItemImage::create(
        normalImage,
        selectedImage,
        CC_CALLBACK_1(CCPopupLayer::buttonCallBack,this));
    item->setTag(tag);
    item->setPosition(center);

    // 添加文字说明并设置位置
    Size itemSize = item->getContentSize();
    auto* ttf = Label::createWithTTF(title, "", 20);
    ttf->setColor(Color3B(0, 0, 0));
    ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
    item->addChild(ttf);

    getMenuButton()->addChild(item);

    return true;
}

void CCPopupLayer::buttonCallBack(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    CCLOG("【====PopupLayer::buttonCallBack====】touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();
}

void CCPopupLayer::onEnter()
{
    LayerColor::onEnter();

    Size winSize = CCDirector::getInstance()->getWinSize();
    Point pCenter = Point(winSize.width / 2, winSize.height / 2);
    //添加背景图片
    auto *background = getSprite9BackGround();
    background->setContentSize(m_dialogContentSize);
    background->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(background,0,0);

    // 弹出效果
    Action* popupLayer = Sequence::create(
        ScaleTo::create(0.0f, 0.0f),
        ScaleTo::create(0.2f, 1.05f),
        ScaleTo::create(0.2f, 0.95f),
        ScaleTo::create(0.1f, 1.0f), 
        CallFunc::create(CC_CALLBACK_0(CCPopupLayer::backgroundFinish,this)),
        NULL
        );
    background->runAction(popupLayer);
}

void CCPopupLayer::backgroundFinish()
{

    Size winSize = CCDirector::getInstance()->getWinSize();
    Point pCenter = Point(winSize.width / 2, winSize.height / 2);

    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = m_dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

    Vector<Node*> vector = getMenuButton()->getChildren();
    Ref* pObj = NULL;
    int i = 0;
    for(Node* pObj : vector){
        Node* node = dynamic_cast<Node*>(pObj);
        node->setPosition(Point( winSize.width / 2 - m_dialogContentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - m_dialogContentSize.height / 3));
        i++;
    }

    // 显示对话框标题
    if (getLabelTitle()){
        getLabelTitle()->setPosition(Vec2(pCenter, Vec2(0, m_dialogContentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());
    }

    // 显示文本内容
    if (getLabelContentText()){
        Label* ltf = getLabelContentText();
        ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        ltf->setDimensions(m_dialogContentSize.width - m_contentPadding * 2, m_dialogContentSize.height - m_contentPaddingTop);
        ltf->setHorizontalAlignment(TextHAlignment::LEFT);
        this->addChild(ltf);
    }
}



void CCPopupLayer::onExit()
{

    CCLOG("popup on exit.");
    CCLayerColor::onExit();
}