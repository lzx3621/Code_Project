#ifndef __CCMENU_SCENE_H__
#define __CCMENU_SCENE_H__

#include "cocos2d.h"

class CCMenuScene :public cocos2d::Scene
{
public:
    CCMenuScene();
    ~CCMenuScene();
    virtual bool init() ;
    CREATE_FUNC(CCMenuScene);
    virtual void addChild(cocos2d::Node* child) override;
    virtual void removeChild(Node* child, bool cleanup = true) override;
    virtual void onEnter() override;
private:
    cocos2d::Node*                      _rootNode;
    cocos2d::Vector<cocos2d::Layer*>    _layers;
};

#endif // __CCMENU_SCENE_H__
