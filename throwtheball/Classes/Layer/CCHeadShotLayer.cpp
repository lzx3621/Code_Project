#include "CCHeadShotLayer.h"
#include "cocostudio/CocoStudio.h"
#include "Expand/SpriteButtom/CCSpriteButtomEvent.h"
#include "AppConfig/CCAppConfig.h"
#include "Expand/ImageScale/CCImageScaleEvent.h"
#include "NDKHelper/NDKHelper.h"
#include "CCDefaultImageLayer.h"
#include "Scene/CCGameScene.h"
#include "Audio/CCAudioHelper.h"
USING_NS_CC;
using namespace cocostudio::timeline;

CCHeadShotLayer::CCHeadShotLayer()
    :_rootNode(nullptr),
    _imageFace(nullptr),
    _fileName("shot.png"),
    _newPicture(false)
{
    CCLOG("CCHeadShotLayer create");
}

CCHeadShotLayer::~CCHeadShotLayer()
{
    CC_SAFE_RELEASE_NULL(_imageFace);
    CC_SAFE_RELEASE_NULL(_rootNode);
    CCLOG("CCHeadShotLayer delete");
    NDKHelper::RemoveSelectorsInGroup("GeadShot");
}

bool CCHeadShotLayer::init()
{
    _rootNode   = CSLoader::createNode("Layer/Headshot/headshot.csb");
    if (!Layer::init() ||
        nullptr == _rootNode)
    {
        return false;
    }
    setName("CCHeadShotLayer");
    _rootNode->retain();
    addChild(_rootNode);
    auto listener = CCSpriteButtomEvent::create();
    listener->onClick = CC_CALLBACK_1(CCHeadShotLayer::onButtomCallback, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
        _rootNode->getChildByName("back"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),
        _rootNode->getChildByName("confirm"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),
        _rootNode->getChildByName("default"));
    listener = listener->clone();
    listener->onClick = CC_CALLBACK_1(CCHeadShotLayer::onButtomSys, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),
            _rootNode->getChildByName("photo"));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(),
            _rootNode->getChildByName("camera"));
     auto listener1 = CCImageScaleEvent::create();
     auto geadshotShow = _rootNode->getChildByName("geadshot_show");
     auto geadshot = geadshotShow->getChildByName("geadshot");

     auto hero = _rootNode->getChildByName<Sprite*>("hero");
     _imageFace = geadshot->getChildByName<Sprite*>("geadshot_Image");
     CC_SAFE_RETAIN(_imageFace);
     listener1->setTarget(_imageFace);
     listener1->setListenNode(geadshotShow);
     getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1,
         geadshotShow);
     geadshot->setContentSize(hero->getContentSize()*hero->getScale());
     geadshot->setPosition(geadshot->getParent()->convertToNodeSpace(hero->getPosition()));
     _imageFace->setPosition(
         Point(geadshot->getContentSize().width/2,
         geadshot->getContentSize().height/2));
     NDKHelper::AddSelector("GeadShot", "showFaceImage", CC_CALLBACK_1(CCHeadShotLayer::showFaceImage, this));
     _imageFace->setTexture(CCAppConfig::getInstance()->getHeroFace());
/*     useClip();*/
    return true;
}

void CCHeadShotLayer::onEnter()
{
    Layer::onEnter();
    _rootNode->getChildByName<Sprite*>("hero")->
        setTexture(CCAppConfig::getInstance()->getHeroSkinPath());
}

void CCHeadShotLayer::onButtomCallback(cocos2d::Node* target)
{
    CCLOG("name :%s", target->getName().c_str());
    if ("back" == target->getName())
    {
        CCAudioHelper::getInstance()->playEffect(1);
        removeFromParent();
    }
    else if ("confirm" == target->getName())
    {
        CCAudioHelper::getInstance()->playEffect(2);
        if (_newPicture)
        {
            screenShot();
            _newPicture = false;
        }
        removeFromParent();
        Director::getInstance()->pushScene(CCGameScene::create());
    }
    else if ("default" == target->getName())
    {
        CCAudioHelper::getInstance()->playEffect(1);
        getParent()->addChild(CCDefaultImageLayer::create());
    }
}

bool CCHeadShotLayer::screenShot()
{
    auto geadshot = _rootNode->getChildByName("geadshot_show")->getChildByName("geadshot");
    /*相对图片的坐标*/
    auto geadshotPos = geadshot->getPosition();
    geadshot->setPosition(_rootNode->convertToNodeSpace(geadshot->getContentSize()/2));
    auto reader = CCRenderTexture::create(geadshot->getContentSize().width,
        geadshot->getContentSize().height);

     reader->begin();
     geadshot->visit();
     reader->end();
     //主动渲染一次，不然没有数据
     if (FileUtils::getInstance()->removeFile(FileUtils::getInstance()->getWritablePath() + _fileName))
     {
         CCLOG("remove success");
     }
     Director::getInstance()->getRenderer()->render();
     if (reader->saveToFile(_fileName,
         cocos2d::Image::Format::PNG))
     {
         CCLOG("save success");
     }
    geadshot->setPosition(geadshotPos);
    
    //如果要显示截图的图片，不移动到中间位置，有空白的地方每次拍照都会录入，
    //新录入的图片包含空白，导致有内容的图片下移，所以要移动到中间
    //_imageFace->setPosition(_imageFace->getParent()->getContentSize()/2);

    callSystemTogetCirclePNG();
    CCAppConfig::getInstance()->setHeroFace(FileUtils::getInstance()->getWritablePath() + _fileName);
    return true;
}

void CCHeadShotLayer::showFaceImage(const cocos2d::Value& value)
{
    auto imageFace = dynamic_cast<Sprite*>(_imageFace);
    if (nullptr != imageFace)
    {
        schedule([=](float){
            if (FileUtils::getInstance()->isFileExist(value.asString().c_str()))
            {
                CCLOG("showFaceImage :%s", value.asString().c_str());
                _newPicture = true;
                Director::getInstance()->getTextureCache()->reloadTexture(value.asString().c_str());
                imageFace->setTexture(value.asString());
                auto pos = imageFace->getPosition();
                auto size = imageFace->getContentSize();
                CCLOG("showFaceImage :%s pos x:%f y:%f, size w:%f, h%f",
                    value.asString().c_str(),
                    pos.x, pos.y,
                    size.width, size.height);
                unschedule("checkTexture");
            }
            else
            {
                CCLOG("%s not Exist", value.asString().c_str());
            }
        },/* 1.0f,*/ "checkTexture");
    }
}

void CCHeadShotLayer::onButtomSys(cocos2d::Node* target)
{
    ValueMap prms;
    prms.insert(make_pair(std::string("filePath"), Value(FileUtils::getInstance()->getWritablePath())));
    prms.insert(make_pair(std::string("fileName"), Value("face.png")));
    CCAudioHelper::getInstance()->playEffect(1);
    if ("photo" == target->getName())
    {
        SendMessageWithParams(std::string("Gallery_Cpp"), 
            Value(prms));
    }
    else if ("camera" == target->getName())
    {
        SendMessageWithParams(std::string("Camera_CPP"),
            Value(prms));
    }
}

void CCHeadShotLayer::callSystemTogetCirclePNG()
{
    auto src = FileUtils::getInstance()->fullPathForFilename(
        FileUtils::getInstance()->getWritablePath() + _fileName);
    auto clip = FileUtils::getInstance()->fullPathForFilename(SZFACEPATH);
    schedule([=](float){
        if (FileUtils::getInstance()->isFileExist(src) &&
            FileUtils::getInstance()->isFileExist(clip))
        {
            unschedule("checkSend");
            ValueMap prm;
            prm.insert(make_pair(std::string("Src"),Value(src)));
            prm.insert(make_pair(std::string("Clip"),Value(clip)));
            SendMessageWithParams("ClipPNG_CPP", Value(prm));
        }
    },
        "checkSend");
}

void CCHeadShotLayer::useClip()
{
    auto clipper = ClippingNode::create(Sprite::create(SZFACEPATH));
    auto geadshot = _rootNode->getChildByName("geadshot_show")->getChildByName("geadshot");
    geadshot->addChild(clipper);
    clipper->setInverted(false);
    clipper->setAlphaThreshold(0);
    clipper->setName("Clipper");
    auto children = geadshot->getChildren().begin();
    auto pos = children[0]->getPosition();
    _imageFace->removeFromParent();
    _imageFace->setPosition(Point::ZERO);
    clipper->addChild(_imageFace);
    clipper->setPosition(geadshot->getContentSize()/2);
}