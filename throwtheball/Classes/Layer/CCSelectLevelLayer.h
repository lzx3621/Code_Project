#ifndef __SELECTLEVEL_LAYER_H__
#define __SELECTLEVEL_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCSelectLevelLayer :public cocos2d::Layer
{
public:
    CCSelectLevelLayer();
    ~CCSelectLevelLayer();
    virtual bool init() ;
    CREATE_FUNC(CCSelectLevelLayer);
protected:

    bool initButtom();
    bool initOption();
    bool initIsLock();
    virtual void onEnter() override;
    //virtual void onExit() override;
    void selectedStateEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void setCheckBoxEnable(cocos2d::ui::CheckBox* cbox, bool enable);

    void onPlayCallback(cocos2d::Node* target);
    void onOpitonCallback(cocos2d::Node* target);
    void onUnlockCallback(cocos2d::Node* target);
    void onIsUnLockCallback(cocos2d::Node* target);
    void updateUnList();
    void initLevelSelect();
private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _option;
    cocos2d::Node* _isUnLock;
    std::string    _UnLockName;
    int            _UnLockMoney;
    int            _bride;
    std::unordered_map<std::string, cocos2d::EventListener*> _listeners;
};

#endif // __SELECTLEVEL_LAYER_H__
