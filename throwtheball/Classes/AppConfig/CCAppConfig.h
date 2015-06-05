#ifndef __APPCONFIG_H__
#define __APPCONFIG_H__
#include "cocos2d.h"
#include "Define.h"


class CCConfigReadAndWriteAdapter;

class CCAppConfig 
{
typedef /*std::map<std::string, cocos2d::Value>*/cocos2d::ValueMap mapValue;
protected:
    CCAppConfig();
    ~CCAppConfig();
    CCAppConfig& operator=(const CCAppConfig&){}
    CCAppConfig(const CCAppConfig&){}
public:
    virtual bool init();
    static CCAppConfig* getInstance();
    static void destroyInstance();

    CC_ATTRIBUTE(std::string, _levelName, LevelName);
    CC_ATTRIBUTE(std::string, _heroSkinPath, HeroSkinPath);
    CC_ATTRIBUTE(std::string, _heroSkinName, HeroSkinName);
    CC_ATTRIBUTE(std::string, _heroFace, HeroFace);
    CC_ATTRIBUTE(bool, _playSound, PlaySound);
    CC_ATTRIBUTE(int, _signInDays, SignInDays);
    CC_SYNTHESIZE_READONLY(tm, _today, Today);
    CC_SYNTHESIZE_READONLY(tm, _yesterday, Yesterday);
    CC_ATTRIBUTE(int, _money, Money);
    CC_ATTRIBUTE(int, _objectFanNum, ObjectFan);
    CC_ATTRIBUTE(int, _objectClockNum, ObjectClock);

    //临时参数不用存储,是否是限时模式
    CC_ATTRIBUTE(bool, _isLimited, IsLimited);
    CC_ATTRIBUTE(bool, _showMarry, ShowMarry);
    CC_ATTRIBUTE(bool, _newBride, NewBride);
    CC_ATTRIBUTE(int, _score, CurrentScore);

    void setLevelIsUnlock(const std::string& key, const cocos2d::Value &val);
    const cocos2d::Value* getLevelIsUnlock(const std::string& key);

    void setLevelScore(const std::string& key, const cocos2d::Value &val);
    const cocos2d::Value* getLevelScore(const std::string& key);

    void setBride(const std::string& bridegroom, const cocos2d::Value &val);
    const cocos2d::Value* getBride(const std::string& bridegroom);
// 
//     void setLevelScore(const std::string& key, const int &val);
//     const int getLevelScore(const std::string& key) const;
//     void setBride(const std::string& bridegroom, const bool &val);
//     const bool getBride(const std::string& bridegroom) const;
//     void setLevelIsUnlock(const std::string& key, const bool &val);
//     const bool getLevelIsUnlock(const std::string& key) const;

    bool checkYesterday();
    bool checkToday();
    void commit();
protected:
    void writeValues();
    void readValues();

    void setMapValue(const std::string &key, const cocos2d::Value &val, mapValue &target);
    cocos2d::Value* getMapValue(const std::string& key, mapValue& target);
    /*std::string getDateNow();*/
    tm* getDateNow() const;
private:
//     template <typename T>
//     void setMapValue(const std::string &key, const T &val, mapValue &target);
//     template <typename T>
//     const T getMapValue(const std::string &key,const mapValue &target) const;
    CCConfigReadAndWriteAdapter* _configReadAndWrite;
    mapValue    _levelIsUnlocks;
    mapValue    _LevelScores;
    mapValue    _brides;
    static CCAppConfig* s_ptrInstance;
};
#endif /*__APPCONFIG_H__*/