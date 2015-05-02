#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"

class CCHeroAdapter;
class CCSupportAdapter;
class CCRoleFactory;
class CCGameUIAdapter;
enum RoleType :int;

typedef std::unordered_map<cocos2d::Sprite*, cocos2d::Vec2> Velocity;
class CCNormalRule :
    public CCRule, public cocos2d::Node
{
protected:
    CCNormalRule();
    ~CCNormalRule(void);
    virtual bool init(CCGameUIAdapter* UIAdapter);
public:
    static CCNormalRule* create(CCGameUIAdapter* UIAdapter);
    virtual void gameStart() override;
    virtual void gameRestart() override;
    virtual void gamePause() override;
    virtual void gameResume() override;
    virtual void gameOver() override;
protected:
    //设置难度
    virtual void setLevel(const int& level);
    //游戏是否继续
    virtual bool isGameContinue(CCHeroAdapter* &hero, CCSupportAdapter* &support);
    virtual int getLevel();
    void createObjectOffFall(float dt);
    virtual bool onHeroTouchBegan(cocos2d::Touch*, cocos2d::Event*) ;
	virtual void onHeroTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) ;
    virtual void onHeroContact(CCHeroAdapter* hero, CCSupportAdapter* support);
    virtual void onObjectContactBottom(CCSupportAdapter* support);

    void addRole(RoleType type);
    void pauseAllRole();
    void resumeAllRole();
protected:
    CCRoleFactory*      _roleFactory;
	cocos2d::Scene*     _gameScene;
    CCGameUIAdapter*    _UIAdapter;
	bool			    _isStart;
private:
    Velocity _velocity;
    int _level;
    int _levelResume;
    int _storeUp;
};

#endif __NORMALRULE_H__