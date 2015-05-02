#ifndef __STORESCENE_SCENE_H__
#define __STORESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCStoreScene :public cocos2d::Scene
{
protected:
    CCStoreScene();
    ~CCStoreScene();
public:
    virtual bool init() ;
    CREATE_FUNC(CCStoreScene);
protected:
    //StoreNode½Úµã
    bool initStoreNode();
//   virtual void onEnterTransitionDidFinish() override;
//    virtual void onExitTransitionDidStart() override;
    void selectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable);
    void PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event);
    void onButtomCallback(cocos2d::Node* target);
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _storeNode;
};

#endif // __STORESCENE_SCENE_H__
