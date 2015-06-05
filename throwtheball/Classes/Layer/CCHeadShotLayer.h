#ifndef __HEADSHOT_LAYER_H__
#define __HEADSHOT_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class CCHeadShotLayer :public cocos2d::Layer
{
protected:
    CCHeadShotLayer();
    ~CCHeadShotLayer();
public:
    virtual bool init() ;
    CREATE_FUNC(CCHeadShotLayer);
protected:
    void selectedEvent(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void onButtomCallback(cocos2d::Node* target);
    void showFaceImage(const cocos2d::Value& value);
    //打开相机和相册，通过easyndk，showFaceImage会被回调
    void onButtomSys(cocos2d::Node* target);
    bool screenShot();
    virtual void onEnter() override;
private:
    //调用系统平台去制作一个圆形按钮图片
    void callSystemTogetCirclePNG();
    void useClip();
    cocos2d::Node*      _rootNode;
    cocos2d::Sprite*    _imageFace;
    //保存当前的文件名，下次按保存要换另外一个
    std::string _fileName;
    bool _newPicture;
};

#endif // __HEADSHOT_LAYER_H__
