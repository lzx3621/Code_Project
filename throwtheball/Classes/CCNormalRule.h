#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"

class CCHeroAdapter;
class CCSupportAdapter;
class CCRoleFactory;

class CCNormalRule :
    public CCRule, public cocos2d::Node
{
protected:
    CCNormalRule(cocos2d::Node* gameScene);
    ~CCNormalRule(void);
    virtual bool init() override;
public:
    static CCNormalRule* create(cocos2d::Node* game);
    virtual void gameStart() override;
    virtual void gameRestart() override;
    virtual void gamePause() override;
    virtual void gameOver() override;
protected:
    void createObjectOffFall(float dt);
    virtual bool onHeroTouchBegan(cocos2d::Touch*, cocos2d::Event*) ;
	virtual void onHeroTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) ;
    virtual void onHeroContact(CCHeroAdapter* hero, CCSupportAdapter* support);
    virtual void onObjectContactBottom(CCSupportAdapter* support);
protected:
    CCRoleFactory*  _roleFactory;
	cocos2d::Node* _gameScene;
	bool			_isStart;
};

#endif __NORMALRULE_H__