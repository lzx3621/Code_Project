
#ifndef __EasyNDK_for_cocos2dx__NDKHelper__
#define __EasyNDK_for_cocos2dx__NDKHelper__

#include "cocos2d.h"
#include "NDKCallbackNode.h"
#include "json/rapidjson.h"
#include "json/document.h"

class NDKHelper
{
    class CCInnerValue: public rapidjson::Value,public cocos2d::Ref
    {
    public:
	    CCInnerValue():rapidjson::Value(){}
        CCInnerValue(rapidjson::Type type):rapidjson::Value(type){}
        CCInnerValue(bool b):rapidjson::Value(b){}
        CCInnerValue(int i):rapidjson::Value(i){}
        CCInnerValue(unsigned u):rapidjson::Value(u){}
        CCInnerValue(int64_t i64):rapidjson::Value(i64){}
        CCInnerValue(uint64_t u64):rapidjson::Value(u64){}
        CCInnerValue(double d):rapidjson::Value(d){}
        CCInnerValue(const Ch* s, rapidjson::SizeType length):rapidjson::Value(s,length){}
        CCInnerValue(const Ch* s):rapidjson::Value(s){}
        CCInnerValue(const Ch* s, rapidjson::SizeType length,rapidjson::Document::AllocatorType& allocator)
            :rapidjson::Value(s,length, allocator){}
        CCInnerValue(const Ch* s, rapidjson::Document::AllocatorType& allocator)
            :rapidjson::Value(s, allocator){}
    private:
	    CCInnerValue(const CCInnerValue& rhs) {};

    };
    private :
        static std::vector<NDKCallbackNode> selectorList;
        static void RemoveAtIndex(int index);

    public :
        static void AddSelector(const char *groupName, const char *name, NDKfunc selector);
        static void RemoveSelectorsInGroup(const char *groupName);
        static void PrintSelectorList();
        static cocos2d::Value GetCCObjectFromJson(const rapidjson::Value& value);
        static CCInnerValue* GetJsonFromCCObject(const cocos2d::Value& value,
            rapidjson::Document::AllocatorType& allocator);
        static void HandleMessage(const rapidjson::Value& methodName, const rapidjson::Value& methodParams);
};

extern "C"
{
    void SendMessageWithParams(std::string methodName, const cocos2d::Value& methodParams);
}

#endif /* defined(__EasyNDK_for_cocos2dx__NDKHelper__) */
