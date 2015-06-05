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
    //���������ᣬͨ��easyndk��showFaceImage�ᱻ�ص�
    void onButtomSys(cocos2d::Node* target);
    bool screenShot();
    virtual void onEnter() override;
private:
    //����ϵͳƽ̨ȥ����һ��Բ�ΰ�ťͼƬ
    void callSystemTogetCirclePNG();
    void useClip();
    cocos2d::Node*      _rootNode;
    cocos2d::Sprite*    _imageFace;
    //���浱ǰ���ļ������´ΰ�����Ҫ������һ��
    std::string _fileName;
    bool _newPicture;
};

#endif // __HEADSHOT_LAYER_H__
