#include "AppDelegate.h"
#include "Scene/CCLoaderScene.h"
#include "AppConfig/CCAppConfig.h"
#include "Audio/CCAudioHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    CCAppConfig::destroyInstance();
    CCAudioHelper::destroyInstance();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("throwtheball", Rect(0, 0, 720, 1280));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
        glview->setFrameSize(360, 640);
#endif
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    FileUtils::getInstance()->addSearchPath("res");
    auto scene = CCLoaderScene::create();
    
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCAppConfig::getInstance()->commit();
    Director::getInstance()->stopAnimation();
    CCAudioHelper::getInstance()->pauseAllAudio();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    CCAudioHelper::getInstance()->resumeAllAudio();
}
