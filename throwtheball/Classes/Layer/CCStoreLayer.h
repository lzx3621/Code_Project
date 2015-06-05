#ifndef __STORE_LAYER_H__
#define __STORE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCStoreLayer :public cocos2d::Layer
{
protected:
    CCStoreLayer();
    ~CCStoreLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCStoreLayer);
protected:
    //StoreNode½Úµã
    bool initStoreNode();
    bool initBuyObjectOK();
    bool initBuyLevelOK();
    bool initBuyFailNotEnough();
    bool initBuyFailAlready();
    bool initButtom();
    void nextPage(cocos2d::Node*);
    void prePage(cocos2d::Node*);
//   virtual void onEnterTransitionDidFinish() override;
//    virtual void onExitTransitionDidStart() override;
    void switchPage(cocos2d::Node* target);
    void selectedEvent(cocos2d::Node* target);
    void PageViewCallback(Ref* ref,cocos2d::ui::PageView::EventType event);
    void onButtomCallback(cocos2d::Node* target);
    void onConfirmBuy(cocos2d::Node*);
    void onConfirm(cocos2d::Node*);
    
private:
    void addListent(cocos2d::ui::Layout* page);
    void showBuyObject(const char * name, int &num);
    
    cocos2d::Node* _rootNode;
    cocos2d::Node* _storeNode;
    cocos2d::Node* _buyObjectOK;
    cocos2d::Node* _buyLevelOK;
    cocos2d::Node* _buyFailNotEnough;
    cocos2d::Node* _buyFailAlready;
    cocos2d::Node* _seclect;
    cocos2d::ui::PageView* _showPage;
};

#endif // __STORE_LAYER_H__
