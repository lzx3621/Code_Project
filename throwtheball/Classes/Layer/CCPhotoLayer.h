#ifndef __PHOTO_LAYER_H__
#define __PHOTO_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCPhotoLayer :public cocos2d::Layer
{
protected:
    CCPhotoLayer();
    ~CCPhotoLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCPhotoLayer);
protected:
    //StoreNode½Úµã
    bool initScrollView();
    void selectedEvent(cocos2d::Node* target);
    void setItemEnable(cocos2d::Node* item, bool enable);
    void onButtomCallback(cocos2d::Node* target);
    void getVector(cocos2d::Vector<Node*> &outEnable,
        cocos2d::Vector<Node*> &outDisable);
    void switchFace();
private:
    cocos2d::Node*      _rootNode;
    cocos2d::Node*      _scrollView;
    cocos2d::Sprite*    _bridegroom;
    cocos2d::Sprite*    _bride;
    cocos2d::Node*    _seclect;
    const int COLUMN;
    const int ROWDIST;
};

#endif // __PHOTO_LAYER_H__
