#include "CCConfigReadAndWriteAdapter.h"
#ifndef __CONFIGFILEADAPTER_H__
#define __CONFIGFILEADAPTER_H__

class CCConfigFileAdapter :
    public CCConfigReadAndWriteAdapter
{
protected:
    CCConfigFileAdapter(void);
    virtual ~CCConfigFileAdapter(void);
public:
    static CCConfigReadAndWriteAdapter* create();
    virtual bool init();
    virtual bool isFirst();
    virtual bool read(const std::string &name /*in*/, cocos2d::Value &value /*out*/);
    virtual bool write(const std::string &name /*in*/,const cocos2d::Value &value /*out*/);
    virtual void commit();
protected:
    bool _first;
private:
    cocos2d::ValueMap _valueMap;
    std::string _flieName;
};

#endif /*__CONFIGFILEADAPTER_H__*/