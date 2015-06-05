#ifndef __SIGNIN_LAYER_H__
#define __SIGNIN_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCSignInLayer :public cocos2d::Layer
{
protected:
    CCSignInLayer();
    ~CCSignInLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCSignInLayer);
protected:
    //StoreNode½Úµã
    bool initGetObject();
    void popThis(float d);

private:
    cocos2d::Node* _rootNode;
    cocos2d::Node* _getObject;

};

#endif // __SIGNIN_LAYER_H__
