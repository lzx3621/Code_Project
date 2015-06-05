#ifndef __LOADER_SCENE_H__
#define __LOADER_SCENE_H__

#include "cocos2d.h"

class CCLoaderScene :public cocos2d::Scene
{
public:
    CCLoaderScene();
    ~CCLoaderScene();
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
protected:
    void loadingFinish();
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _loading;
    cocos2d::Node* _finish;
    cocos2d::Point _originalPosition;
    bool _showOther;
    bool _finishok;
};

#endif // __LOADER_SCENE_H__
