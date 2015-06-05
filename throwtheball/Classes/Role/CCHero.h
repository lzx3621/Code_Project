#ifndef __CCHERO_SPRITE_H__
#define __CCHERO_SPRITE_H__

#include "Define.h"
#include "cocostudio/CocoStudio.h"
#include "CCRole.h"

//主角类应当为在一个游戏模式中应该为单例存在

class CCHero : public SuperRole, public Sprite
{
protected:
    CCHero():
        SuperRole(MAIN_HERO, 5, 0), 
        _pos(cocos2d::Point::ZERO),
        _armature(nullptr),
        _vectTemp(Vect::ZERO),
        _currPlay("huishou"){}
    ~CCHero();
    CREATE_FUNC(CCHero);
    virtual void update(float delta) override;
    virtual void onEnter() override;
    virtual void pause(void) override;
    virtual void resume(void) override;
    //virtual void setPosition(float x, float y);
public:
    bool init() override;
    bool initFromCsb();
    void walk();
    void get();
    void stand();
    cocos2d::Point _pos;
protected:
    void getObjectCallBack(cocostudio::Armature *armature, 
        cocostudio::MovementEventType movementType, 
        const std::string& movementID);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void switchFace();
    cocostudio::Armature* _armature;
    std::string _currPlay;
    cocos2d::Vect _vectTemp;
    friend class CCRoleFactory;
    friend class CCHeroAdapterOfPhysics;
};

#endif // __CCHERO_SPRITE_H__