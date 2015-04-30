#ifndef __POPUPLAYER_H__
#define __POPUPLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCPopupLayer : public cocos2d::LayerColor{
public:
    CCPopupLayer();
    ~CCPopupLayer();

    virtual bool init();
    CREATE_FUNC(CCPopupLayer);
    static CCPopupLayer* create(const char* backgroundImage,cocos2d::Size dialogSize);

    //touch�¼����� �������´���
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);

    //����
    void setTitle(const char* title, int fontsize = 20);
    //�ı�
    void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddintTop = 100);
    //����button�ص��¼�
    void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callfun);
    //���button
    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

    virtual void onEnter();
    virtual void onExit();

    void backgroundFinish();

private:

    void buttonCallBack(cocos2d::Ref* pSender);

    // �����������ߵĿհ���
    int m_contentPadding;
    int m_contentPaddingTop;

    cocos2d::Size m_dialogContentSize;

    cocos2d::Ref* m_callbackListener;
    cocos2d::SEL_CallFuncN m_callback;
    
    //set and get
    CC_SYNTHESIZE_RETAIN(cocos2d::Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(cocos2d::ui::ImageView*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, m__ltContentText, LabelContentText);
};
#endif __POPUPLAYER_H__