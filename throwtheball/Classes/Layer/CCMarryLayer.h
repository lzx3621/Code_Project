#ifndef __MARRY_LAYER_H__
#define __MARRY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCMarryLayer :public cocos2d::Layer
{
protected:
    CCMarryLayer();
    ~CCMarryLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCMarryLayer);
protected:
    void switchFace();
    void setBrideAndBridegroom(int score);
    void onOpitonCallback(cocos2d::Node* target);
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _getObject;

};

#endif // __MARRY_LAYER_H__
