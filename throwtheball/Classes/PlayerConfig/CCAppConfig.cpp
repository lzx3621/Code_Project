#include "CCAppConfig.h"
#include "Adapter\CConfigFileAdapter.h"
USING_NS_CC;

CCAppConfig* CCAppConfig::s_Instance = nullptr;

CCAppConfig::CCAppConfig():
    configReadAndWrite(CCConfigFileAdapter::create()),
    _heroName("waiter"),
    _playSound(true)
{
    for (auto score : _highestScores)
    {
        score = 0;
    }
    for (auto unLockIsUnlock: _unLockIsUnlocks)
    {

    }
}

CCAppConfig::~CCAppConfig()
{

}

bool CCAppConfig::init()
{
    if (nullptr == configReadAndWrite)
    {
        CCLOG("configReadAndWrite");
        return false;
    }
    if (configReadAndWrite->isFirst())
    {
        readValues();
    }
    else
    {
        writeValues();
    }
    return true;
}

void CCAppConfig::writeValues()
{
    configReadAndWrite->write("heroName", _heroName);
    configReadAndWrite->write("playSound", _playSound);
    int i(0);
    char szch[10]= {0};
    for (auto score : _highestScores)
    {
        sprintf(szch, "score%d", i++);
        configReadAndWrite->write(szch,score);
    }
    for (auto _unLock : _unLockIsUnlocks)
    {
        sprintf(szch, "Level%d", i++);
        configReadAndWrite->write(szch,_unLock);
    }
}

void CCAppConfig::readValues()
{
    configReadAndWrite->read("heroName", _heroName);
    configReadAndWrite->read("playSound", _playSound);
    int i(0);
    char szch[10]= {0};
    for (auto score : _highestScores)
    {
        sprintf(szch, "score%d", i++);
        configReadAndWrite->read(szch,score);
    }
    for (auto _unLock : _unLockIsUnlocks)
    {
        sprintf(szch, "Level%d", i++);
        configReadAndWrite->read(szch,_unLock);
    }
}

CCAppConfig* CCAppConfig::getInstance()
{
    if (nullptr == s_Instance)
    {
        s_Instance = new CCAppConfig();
    }
    return s_Instance;
}
