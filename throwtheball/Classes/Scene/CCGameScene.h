#ifndef __GAMESCENENORMAL_SCENE_H__
#define __GAMESCENENORMAL_SCENE_H__

#include "cocos2d.h"
#include "./Rule/CCRule.h"
#include "./Adapter/CCGameUIAdapter.h"

class CCGameScene :
    public cocos2d::Scene, public CCGameUIAdapter
{
public:
    CCGameScene();
    ~CCGameScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    CREATE_FUNC(CCGameScene);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() ;

    virtual cocos2d::Scene* getGameScene();
    virtual void addRole(cocos2d::Node* Role);
    virtual void removeAllRole();
    virtual void showPauseUI();
    virtual void hidePauseUI();
    virtual void showGameOverUI(const int &score);
    virtual void hideGameOverUI();
    virtual cocos2d::Vector<cocos2d::Node*>& getRole();
    virtual void showHaze();
    virtual void hideHaze();
    virtual void showToast();
    virtual void hideToast();
    virtual void setlimited(bool set);

    // implement the "static create()" method manually
protected:
    virtual void updateHeroScoreAndLive(const int& Hero, const int& score);
    virtual void updateTime(const int& time);
    virtual void onEnter() override;
    virtual void onExit() override;

    void puase(cocos2d::Node*);
    void buttonCallback(cocos2d::Node*);
    void gameOverCallback(cocos2d::Node* target);

    bool onHydrangeaTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) ;
    void onHydrangeaTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) ;
    
    void showHaze2();
    void changeBackground();
    void initObject();
    void useObject(cocos2d::Node* target);

    bool initPuaseLayer();
    bool initGameOverLayer();
    bool initRoot();
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _pauseLayer;
    cocos2d::Node* _gameOverLayer;
    bool _pauseLayerShow;
    bool _gameOverLayerShow;
    bool _toastShow;
    bool _hazeShow;
    bool _redTime;
};

#endif // __HELLOWORLD_SCENE_H__
