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
         ValueMap appConfig = fileUtil->getValueMapFromFile(_flieName);
         _first = false;
     }
     else
     {
         _first = true;
     }
     return true;
}

CCConfigReadAndWriteAdapter* CCConfigFileAdapter::create()
{
    auto ret = new CCConfigFileAdapter();
    if (nullptr == ret)
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
    auto iter = _valueMap.find(name);
    if (_valueMap.end() != iter)
    {
        value = iter->second;
        return true;
    }
    else
    {
        return false;
    }
}

bool CCConfigFileAdapter::write(const std::string &name /*in*/,const cocos2d::Value &value /*out*/)
{
    auto iter = _valueMap.find(name);
    if (_valueMap.end() != iter)
    {
        iter->second = value;
        return true;
    }
    else
    {
        _valueMap.insert(make_pair(name, value));
        return false;
    }
}

void CCConfigFileAdapter::commit()
{
    FileUtils::getInstance()->writeToFile(_valueMap, _flieName);
}
