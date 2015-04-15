#ifndef __GAMESCENENORMAL_SCENE_H__
#define __GAMESCENENORMAL_SCENE_H__

#include "cocos2d.h"
#include "CCRule.h"
#include "CCGameUIAdapter.h"

class CCGameScene :
    public cocos2d::Layer, public CCGameUIAdapter
{
public:
    CCGameScene(){}
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(cocos2d::Scene*) ;

    virtual void addChild(Node * child);

    virtual cocos2d::Scene* getGameScene();
    virtual void addRole(cocos2d::Node* Role);
    // implement the "static create()" method manually
protected:
    static CCGameScene* create(cocos2d::Scene* scene);

    virtual void updateheroScoreAndLive(int Hero, int score);
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;
};

#endif // __HELLOWORLD_SCENE_H__
