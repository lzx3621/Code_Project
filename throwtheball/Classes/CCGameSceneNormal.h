#ifndef __GAMESCENENORMAL_SCENE_H__
#define __GAMESCENENORMAL_SCENE_H__

#include "cocos2d.h"
#include "CCRule.h"

class CCGameSceneNormal : public cocos2d::Layer
{
public:
    CCGameSceneNormal(){}
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(CCGameSceneNormal);

    void startGame();

};

#endif // __HELLOWORLD_SCENE_H__
