#ifndef __NORMALRULE_H__
#define __NORMALRULE_H__
#include "CCRule.h"

class CCHeroAdapter;
class CCSupportAdapter;
class CCRoleFactory;
class CCGameUIAdapter;
enum RoleType :int;

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
    virtual bool useObject(const std::string& Object) override;
protected:
    //设置难度
    virtual void setLevel(const int& level);
    //游戏是否继续
    virtual bool isGameContinue(CCHeroAdapter &hero, CCSupportAdapter &support);
    virtual int getLevel();
    virtual void createObjectOffFall(float dt);
    virtual void onHeroContact(CCHeroAdapter& hero, CCSupportAdapter& support);
    virtual void onObjectContactBottom(CCSupportAdapter& support);

    void addRole(RoleType type);
    void pauseAllRole();
    void resumeAllRole();
protected:
    CCRoleFactory*      _roleFactory;
	cocos2d::Scene*     _gameScene;
    CCGameUIAdapter*    _UIAdapter;
	bool			    _isStart;
    int                 _currScore;
    cocos2d::Sprite*    _hero;
    int                 _numGain;
    int                 _numDamage;
    const int           ROLEMAX;

    int _level;
    int _levelResume;
    int _storeUp;
    bool _pauseAllRole;
};

#endif /*__NORMALRULE_H__*/