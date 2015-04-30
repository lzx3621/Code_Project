#ifndef __LOADER_SCENE_H__
#define __LOADER_SCENE_H__

#include "cocos2d.h"

class CCLoaderScene :public cocos2d::Scene
{
public:
    CCLoaderScene();
    ~CCLoaderScene();
    static cocos2d::Scene* createScene();

    virtual bool init() ;
    CREATE_FUNC(CCLoaderScene);
protected:
    bool initloading();
    bool initfinish();
    virtual void onEnterTransitionDidFinish() override;
//    virtual void onExitTransitionDidStart() override;
    static void initResourceAndPlayer(CCLoaderScene* pthis);
    bool onHydrangeaTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) ;
    void onHydrangeaTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) ;
    void onHydrangeaTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) ;

private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _loading;
    cocos2d::Node* _finish;
};

#endif // __LOADER_SCENE_H__
