#ifndef __SELECTLEVEL_SCENE_H__
#define __SELECTLEVEL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCSelectLevelScene :public cocos2d::Scene
{
public:
    CCSelectLevelScene();
    ~CCSelectLevelScene();
    static cocos2d::Scene* createScene();

    virtual bool init() ;
    CREATE_FUNC(CCSelectLevelScene);
protected:
    //下半部分
    bool initMenu();
    //上半部分选择的
    bool initSelect();
//   virtual void onEnterTransitionDidFinish() override;
//    virtual void onExitTransitionDidStart() override;
    void selectedStateEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable);

    void onPlayCallback(cocos2d::Node* target);
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _CheckGroup;
};

#endif // __SELECTLEVEL_SCENE_H__
