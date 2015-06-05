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
    virtual void commit() = 0;
    virtual bool read(const std::string &name /*in*/, cocos2d::Value &value /*out*/) = 0;
    virtual bool write(const std::string &name /*in*/,const cocos2d::Value &value /*out*/) = 0;
    template<typename T> inline bool read(const std::string &name /*in*/, T &value /*out*/)
    {
        cocos2d::Value outValue = cocos2d::Value::Null;
        if (read(name, outValue))
        {
            //有点危险的转换
            switch (outValue.getType())
            {
            case cocos2d::Value::Type::BYTE:
                {
                    auto var = outValue.asByte();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::INTEGER:
                {
                    auto var = outValue.asInt();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::FLOAT:
                {
                    auto var = outValue.asFloat();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::DOUBLE:
                {
                    auto var = outValue.asDouble();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::BOOLEAN:
                {
                    auto var = outValue.asBool();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::STRING:
                {
                    auto var = outValue.asString();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::VECTOR:
                {
                    auto var = outValue.asValueVector();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::MAP:
                {
                    auto var = outValue.asValueMap();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::INT_KEY_MAP:
                {
                    auto var = outValue.asIntKeyMap();
                    value = *reinterpret_cast<T*>(&var);
                }
                break;
            case cocos2d::Value::Type::NONE:
            default:
                return false;
                break;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T> inline bool write(const std::string &name /*in*/,const T &value /*out*/)
    {
        return write(name, cocos2d::Value(value));
    }
};

#endif /*__CONFIGREADANDWRITE_ADAPTER_H__*/