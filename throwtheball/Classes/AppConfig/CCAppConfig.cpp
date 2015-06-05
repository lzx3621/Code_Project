#include "CCAppConfig.h"
#include "Adapter\CConfigFileAdapter.h"
USING_NS_CC;

CCAppConfig* CCAppConfig::s_ptrInstance = nullptr;

CCAppConfig::CCAppConfig():
    _configReadAndWrite(CCConfigFileAdapter::create()),
    _levelName("waiter"),
    _heroSkinName("waiter"),
    _heroSkinPath("Layer/Headshot/Hero/waiter.png"),
    _heroFace(SZFACEPATH),
    _playSound(true),
    _signInDays(0),
    _money(99999),
    _objectFanNum(0),
    _objectClockNum(0),
    _isLimited(false),
    _showMarry(false),
    _newBride(false),
    _score(0)
{
    _levelIsUnlocks.insert(make_pair(std::string("cateran"), Value(false)));
    _levelIsUnlocks.insert(make_pair(std::string("general"), Value(false)));
    _levelIsUnlocks.insert(make_pair(std::string("scholar"), Value(false)));
    _levelIsUnlocks.insert(make_pair(std::string("waiter"), Value(true)));
    _LevelScores.insert(make_pair(std::string("cateran"), Value(0)));
    _LevelScores.insert(make_pair(std::string("general"), Value(0)));
    _LevelScores.insert(make_pair(std::string("scholar"), Value(0)));
    _LevelScores.insert(make_pair(std::string("waiter"),  Value(0)));
    ValueVector bridesUnlock;
    for (int i(0); i < 9; i++)
    {
        bridesUnlock.push_back(Value(false));
    }
    _brides.insert(make_pair(std::string("cateran"), Value(bridesUnlock)));
    _brides.insert(make_pair(std::string("general"), Value(bridesUnlock)));
    _brides.insert(make_pair(std::string("scholar"), Value(bridesUnlock)));
    _brides.insert(make_pair(std::string("waiter"),  Value(bridesUnlock)));
    memset(&_today, 0, sizeof(_today));
    memset(&_yesterday, 0, sizeof(_yesterday));
}

CCAppConfig::~CCAppConfig()
{
    commit();
    CC_SAFE_DELETE(_configReadAndWrite);
    CCLOG("CCAppConfig delete");
}

bool CCAppConfig::init()
{
    if (nullptr == _configReadAndWrite)
    {
        CCLOGERROR("configReadAndWrite is null");
        return false;
    }
    auto tm = getDateNow();
    _today.tm_year  = tm->tm_year + 1900;
    _today.tm_mon   = tm->tm_mon + 1;
    _today.tm_mday  = tm->tm_mday;
    if (_configReadAndWrite->isFirst())
    {
        writeValues();
        _yesterday.tm_year  = tm->tm_year + 1900;
        _yesterday.tm_mon   = tm->tm_mon + 1;
        _yesterday.tm_mday  = tm->tm_mday - 1;
        _configReadAndWrite->commit();
    }
    else
    {
        readValues();
    }
    return true;
}

void CCAppConfig::writeValues()
{
    _configReadAndWrite->write<std::string>("HeroName", _levelName);
    _configReadAndWrite->write<bool>("PlaySound", _playSound);
    _configReadAndWrite->write<int>("SignInDays", _signInDays);
    _configReadAndWrite->write<int>("Money", _money);
    _configReadAndWrite->write<int>("ObjectFan", _objectFanNum);
    _configReadAndWrite->write<int>("ObjectClock", _objectClockNum);
    _configReadAndWrite->write<std::string>("HeroSkinPath", _heroSkinPath);
    _configReadAndWrite->write<std::string>("HeroSkinName", _heroSkinName);
    _configReadAndWrite->write<std::string>("HeroFace", _heroFace);
    _yesterday.tm_year  = _today.tm_year;
    _yesterday.tm_mon   = _today.tm_mon;
    _yesterday.tm_mday  = _today.tm_mday;
     char szch[20]= {0};
    sprintf(szch, "%d-%02d-%02d", (int) _yesterday.tm_year,  
        (int) _yesterday.tm_mon, (int) _yesterday.tm_mday ); 
    _configReadAndWrite->write("Yesterday", Value(szch));
    _configReadAndWrite->write<mapValue>("Level", _levelIsUnlocks);
    _configReadAndWrite->write<mapValue>("Score", _LevelScores);
    _configReadAndWrite->write<mapValue>("Bride", _brides);
}

void CCAppConfig::readValues()
{
    _configReadAndWrite->read<std::string>("HeroName", _levelName);
    _configReadAndWrite->read<bool>("PlaySound", _playSound);
    _configReadAndWrite->read<int>("SignInDays", _signInDays);
    _configReadAndWrite->read<int>("Money", _money);
    _configReadAndWrite->read<int>("ObjectFan", _objectFanNum);
    _configReadAndWrite->read<int>("ObjectClock", _objectClockNum);
    _configReadAndWrite->read<std::string>("HeroSkinPath", _heroSkinPath);
    _configReadAndWrite->read<std::string>("HeroSkinName", _heroSkinName);
    _configReadAndWrite->read<std::string>("HeroFace", _heroFace);
    Value yesterday ;
    _configReadAndWrite->read("Yesterday", yesterday);
    sscanf(yesterday.asString().c_str(), "%d-%02d-%02d", &_yesterday.tm_year,  
        &_yesterday.tm_mon , &_yesterday.tm_mday ); 
    _configReadAndWrite->read<mapValue>("Level", _levelIsUnlocks);
    _configReadAndWrite->read<mapValue>("Score", _LevelScores);
    _configReadAndWrite->read<mapValue>("Bride", _brides);
}

CCAppConfig* CCAppConfig::getInstance()
{
    if (nullptr == s_ptrInstance)
    {
        s_ptrInstance = new CCAppConfig();
        s_ptrInstance->init();
    }
    return s_ptrInstance;
}

void CCAppConfig::setMapValue(const std::string &key, const cocos2d::Value &val, mapValue &target)
{
    auto iter = target.find(key);
    if (target.end() != iter)
    {
        iter->second = val;
    }
}

cocos2d::Value* CCAppConfig::getMapValue(const std::string& key, mapValue& target)
{
    auto iter = target.find(key);
    if (target.end() == iter)
    {
        return nullptr;
    }
    return &(iter->second);
}

void CCAppConfig::setLevelIsUnlock(const std::string& key, const cocos2d::Value &val)
{
    setMapValue(key, val, _levelIsUnlocks);
}

// void CCAppConfig::setLevelIsUnlock(const std::string& key, const bool &val)
// {
//     setMapValue<bool>(key, val, _levelIsUnlocks);
// }

const cocos2d::Value* CCAppConfig::getLevelIsUnlock(const std::string& key)
{
    return getMapValue(key, _levelIsUnlocks);
}

// const bool CCAppConfig::getLevelIsUnlock(const std::string& key) const
// {
//     return getMapValue<bool>(key, _levelIsUnlocks);
// }

const cocos2d::Value* CCAppConfig::getLevelScore(const std::string& key)
{
    return getMapValue(key, _LevelScores);
}
// 
// const int CCAppConfig::getLevelScore(const std::string& key) const
// {
//     return getMapValue<int>(key, _LevelScores);
// }

void CCAppConfig::setLevelScore(const std::string& key, const cocos2d::Value &val)
{
    setMapValue(key, val, _LevelScores);
}

// void CCAppConfig::setLevelScore(const std::string& key, const int &val)
// {
//     setMapValue<int>(key, val, _LevelScores);
// }

void CCAppConfig::destroyInstance()
{
    CC_SAFE_DELETE(s_ptrInstance);
}


tm* CCAppConfig::getDateNow() const
{
    tm *tm;  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
    timeval now;  
    gettimeofday(&now, NULL);
    time_t timep = now.tv_sec; 
#endif  
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )  
    time_t timep;
    time(&timep);
#endif  
    tm = localtime(&timep); 
    return tm;
}

bool CCAppConfig::checkYesterday()
{
    if (_today.tm_year  == _yesterday.tm_year &&
        _today.tm_mon  == _yesterday.tm_mon)
    {
        if ((_yesterday.tm_mday + 1) == _today.tm_mday)
        {
            return true;
        }
    }
    return false;
}

bool CCAppConfig::checkToday()
{
    if (_today.tm_year  == _yesterday.tm_year &&
        _today.tm_mon  == _yesterday.tm_mon)
    {
        if (_yesterday.tm_mday == _today.tm_mday)
        {
            return true;
        }
    }
    return false;
}

void CCAppConfig::setBride(const std::string& bridegroom, const cocos2d::Value &val)
{
    setMapValue(bridegroom, val, _brides);
}

// void CCAppConfig::setBride(const std::string& bridegroom, const bool &val)
// {
//     setMapValue<bool>(bridegroom, val, _brides);
// }

const cocos2d::Value* CCAppConfig::getBride(const std::string& bridegroom)
{
    return getMapValue(bridegroom, _brides);
}

// const bool CCAppConfig::getBride(const std::string& bridegroom) const
// {
//     return getMapValue<bool>(bridegroom, _brides);
// }

void CCAppConfig::commit()
{
    writeValues();
    _configReadAndWrite->commit();
}

// 
// template <typename T>
// const T CCAppConfig::getMapValue(const std::string &key,const mapValue &target) const
// {
//     auto iter = target.find(key);
//     if (target.end() == iter)
//     {
//         return nullptr;
//     }
//     T ret;
//     //有点危险的转换
//     switch (iter->second.getType())
//     {
//     case cocos2d::Value::Type::BYTE:
//         {
//             auto var /*= iter->second.asByte()*/;
//             ret = *reinterpret_cast<T*>(&(iter->second.asByte()));
//         }
//         break;
//     case cocos2d::Value::Type::INTEGER:
//         {
//             auto var = iter->second.asInt();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::FLOAT:
//         {
//             auto var = iter->second.asFloat();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::DOUBLE:
//         {
//             auto var = iter->second.asDouble();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::BOOLEAN:
//         {
//             auto var = iter->second.asBool();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::STRING:
//         {
//             auto var = iter->second.asString();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::VECTOR:
//         {
//             auto var = iter->second.asValueVector();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::MAP:
//         {
//             auto var = iter->second.asValueMap();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::INT_KEY_MAP:
//         {
//             auto var = iter->second.asIntKeyMap();
//             ret = *reinterpret_cast<T*>(&var);
//         }
//         break;
//     case cocos2d::Value::Type::NONE:
//     default:
//         break;
//     }
//     return ret;
// }
// 
// template <typename T>
// void CCAppConfig::setMapValue(const std::string &key, const T &val, mapValue &target)
// {
//     auto iter = target.find(key);
//     if (target.end() != iter)
//     {
//         iter->second = val;
//     }
// }
