#include "CConfigFileAdapter.h"
#include "CCFileUtils.h"

USING_NS_CC;

CCConfigFileAdapter::CCConfigFileAdapter(void):
    _first(true)
{
}


CCConfigFileAdapter::~CCConfigFileAdapter(void)
{
    commit();
}

bool CCConfigFileAdapter::init()
{
     auto fileUtil = FileUtils::getInstance();
     if (nullptr == fileUtil)
     {
         return false;
     }
     _flieName += fileUtil->getWritablePath();
     _flieName += "appConfig.plist";
     if (fileUtil->isFileExist(_flieName))
     {
         CCLOG("file exist");
         _appConfig = fileUtil->getValueMapFromFile(_flieName);
         CCLOG("get config from file values: %s", ValueToString(Value(_appConfig)).c_str());
         _first = false;
     }
     else
     {
         CCLOG("file not exist");
         _first = true;
     }
     return true;
}

CCConfigReadAndWriteAdapter* CCConfigFileAdapter::create()
{
    auto ret = new CCConfigFileAdapter();
    if (nullptr != ret)
    {
        if (!ret->init())
        {
            delete ret;
            ret = nullptr;
        }
    }
    return ret;
}

bool CCConfigFileAdapter::isFirst()
{
    return _first;
}

bool CCConfigFileAdapter::read(const std::string &name /*in*/, cocos2d::Value &value /*out*/)
{
    auto iter = _appConfig.find(name);
    if (_appConfig.end() != iter)
    {
        value = iter->second;
        CCLOG("read name :%s, value:%s",name.c_str(), ValueToString(value).c_str());
        return true;
    }
    else
    {
        CCLOG("read faild");
        return false;
    }
}

bool CCConfigFileAdapter::write(const std::string &name /*in*/,const cocos2d::Value &value /*out*/)
{
    auto iter = _appConfig.find(name);
    if (_appConfig.end() != iter)
    {
        CCLOG("write replace name :%s, value:%s",name.c_str(), ValueToString(value).c_str());
        iter->second = value;
        return true;
    }
    else
    {
        CCLOG("write new name :%s, value:%s",name.c_str(), ValueToString(value).c_str());
        _appConfig.insert(make_pair(name, value));
        return false;
    }
    CCLOG("write config ok values: %s", ValueToString(Value(_appConfig)).c_str());
}

void CCConfigFileAdapter::commit()
{
    if (FileUtils::getInstance()->writeToFile(_appConfig, _flieName))
    {
        CCLOG("commit config ok values: %s", ValueToString(Value(_appConfig)).c_str());
    }
    else
    {
        CCLOG("commit config faild");
    }
}

std::string CCConfigFileAdapter::ValueToString(const cocos2d::Value &value)
{
    std::string ret;
    switch (value.getType())
    {
    case cocos2d::Value::Type::BYTE:
    case cocos2d::Value::Type::INTEGER:
    case cocos2d::Value::Type::FLOAT:
    case cocos2d::Value::Type::DOUBLE:
    case cocos2d::Value::Type::BOOLEAN:
    case cocos2d::Value::Type::STRING:
        {
            ret = "\n value :" + value.asString();
        }
        break;
    case cocos2d::Value::Type::VECTOR:
        {
            ret = "Vector: " ; 
            auto vect = value.asValueVector();
            for (auto &iter:vect)
            {
                ret += "\n" + ValueToString(iter);
            }
        }
        break;
    case cocos2d::Value::Type::MAP:
    case cocos2d::Value::Type::INT_KEY_MAP:
        {
            ret = "MAP: " ; 
            auto vect = value.asValueMap();
            for (auto &iter:vect)
            {
                ret += "\n key :" + iter.first;
                ret += " value :" + ValueToString(iter.second);
            }
        }
        break;
    case cocos2d::Value::Type::NONE:
    default:
        break;
    }
    return ret;
}
