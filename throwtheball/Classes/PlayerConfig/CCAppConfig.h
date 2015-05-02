#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__
#include "cocos2d.h"


class CCConfigReadAndWriteAdapter;

class CCAppConfig 
{
protected:
    CCAppConfig();
    ~CCAppConfig();
    CCAppConfig& operator=(const CCAppConfig&){}
    CCAppConfig(const CCAppConfig&){}
public:
    virtual bool init();
    static CCAppConfig* getInstance();

    CC_SYNTHESIZE(cocos2d::Value, _heroName, HeroName);
    CC_SYNTHESIZE(cocos2d::Value, _unLockIsUnlocks[4], LevelIsUnlocks);
    CC_SYNTHESIZE(cocos2d::Value, _playSound, PlaySound);
    CC_SYNTHESIZE(cocos2d::Value, _highestScores[4], HighestScores);
protected:
    void writeValues();
    void readValues();
private:
    CCConfigReadAndWriteAdapter* configReadAndWrite;
    static CCAppConfig* s_Instance;
};

#endif __APPCONFIG_H__