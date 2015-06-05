#ifndef __DEFAULTIMAGE_LAYER_H__
#define __DEFAULTIMAGE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCDefaultImageLayer :public cocos2d::Layer
{
protected:
    CCDefaultImageLayer();
    ~CCDefaultImageLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCDefaultImageLayer);
protected:
    //StoreNode½Úµã
//   virtual void onEnterTransitionDidFinish() override;
//    virtual void onExitTransitionDidStart() override;
    void selectedEvent(cocos2d::Node* target);
    void setCheckBoxEnable(cocos2d::Node* item, bool enable);
    void PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event);
    void onButtomCallback(cocos2d::Node* target);
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _listNode;
    cocos2d::Node* _detailLayer;
    cocos2d::Node* _seclect;
};

#endif // __DEFAULTIMAGE_LAYER_H__
