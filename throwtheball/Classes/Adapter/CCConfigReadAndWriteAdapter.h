#ifndef __CONFIGREADANDWRITE_ADAPTER_H__
#define __CONFIGREADANDWRITE_ADAPTER_H__
#include "cocos2d.h"

class CCConfigReadAndWriteAdapter
{
public:
    CCConfigReadAndWriteAdapter(void){}
    ~CCConfigReadAndWriteAdapter(void){}

    virtual bool init() = 0;
    virtual bool isFirst() = 0;
    virtual bool read(const std::string &name /*in*/, cocos2d::Value &value /*out*/) = 0;
    virtual bool write(const std::string &name /*in*/,const cocos2d::Value &value /*out*/) = 0;
    virtual void commit() = 0;
};

#endif /*__CONFIGREADANDWRITE_ADAPTER_H__*/