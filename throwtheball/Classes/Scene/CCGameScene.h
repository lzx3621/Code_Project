#ifndef __GAMESCENENORMAL_SCENE_H__
#define __GAMESCENENORMAL_SCENE_H__

#include "cocos2d.h"
#include "./Rule/CCRule.h"
#include "./Adapter/CCGameUIAdapter.h"

class CCGameScene :
    public cocos2d::Layer, public CCGameUIAdapter
{
public:
    CCGameScene():_pauseLayer(nullptr), _rootNode(nullptr),_pauseLayerShow(false){}
    ~CCGameScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(cocos2d::Scene*) ;

    virtual cocos2d::Scene* getGameScene();
    virtual void addRole(cocos2d::Node* Role);
    virtual void showPauseUI();
    virtual void hidePauseUI();
    virtual cocos2d::Vector<cocos2d::Node*>& getRole();

    // implement the "static create()" method manually
protected:
    static CCGameScene* create(cocos2d::Scene* scene);

    virtual void updateheroScoreAndLive(const int& Hero, const int& score);
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;

    void back(Ref*);
    void restart(Ref*);
    void resume(Ref*);
    void puase(Ref*);

    bool initPuase();
    bool initRoot();
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _pauseLayer;
    bool _pauseLayerShow;
};

#endif // __HELLOWORLD_SCENE_H__
