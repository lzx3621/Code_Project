#include "NDKHelper.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#define __CALLED_METHOD__           "calling_method_name"
#define __CALLED_METHOD_PARAMS__    "calling_method_params"

USING_NS_CC;

std::vector<NDKCallbackNode> NDKHelper::selectorList;

void NDKHelper::AddSelector(const char *groupName, const char *name, NDKfunc selector)
{
    NDKHelper::selectorList.push_back(NDKCallbackNode(groupName, name, selector));
}

void NDKHelper::RemoveAtIndex(int index)
{
    NDKHelper::selectorList[index] = NDKHelper::selectorList.back();
    NDKHelper::selectorList.pop_back();
}

void NDKHelper::RemoveSelectorsInGroup(const char *groupName)
{
    std::vector<int> markedIndices;
    
    for (unsigned int i = 0; i < NDKHelper::selectorList.size(); ++i)
    {
        if (NDKHelper::selectorList[i].getGroup().compare(groupName) == 0)
        {
            markedIndices.push_back(i);
        }
    }
    
    for (unsigned int i = 0; i < markedIndices.size(); ++i)
    {
        NDKHelper::RemoveAtIndex(markedIndices[i]);
    }
}

cocos2d::Value NDKHelper::GetCCObjectFromJson(const rapidjson::Value& value)
{
    switch (value.GetType())
    {
    case rapidjson::Type::kFalseType:
    case rapidjson::Type::kTrueType:
        {
            CCLOG("Value Bool");
            return Value(value.GetBool());
        }
    case rapidjson::Type::kObjectType:
        {
            CCLOG("Value Object");
            ValueMap map;
            for (auto iter = value.MemberonBegin();
                iter != value.MemberonEnd(); 
                iter++)
            {
                map.insert(make_pair(std::string(iter->name.GetString()), 
                    NDKHelper::GetCCObjectFromJson(iter->value)));
            }
            return Value(map);
        }
    case rapidjson::Type::kArrayType:
        {
            CCLOG("Value Array");
            ValueVector vector;
            for (rapidjson::SizeType i = 0; i < value.Size(); i++)
            {
                vector.push_back(NDKHelper::GetCCObjectFromJson(value[i]));
            }
            return Value(vector);
        }
    case rapidjson::Type::kStringType:
        {
            CCLOG("Value String");
            return Value(value.GetString());
        }
    case rapidjson::Type::kNumberType:
        {
            CCLOG("Value Number");
            if (value.IsDouble())
            {
                return Value(value.GetDouble());
            }
            else
            {
                return Value(value.GetInt());
            }
        }
    case rapidjson::Type::kNullType:
    default:
        {
            CCLOG("Value Null");
            return Value::Null;
        }
    }
}

NDKHelper::CCInnerValue* NDKHelper::GetJsonFromCCObject(const cocos2d::Value& value, rapidjson::Document::AllocatorType& allocator)
{
    CCInnerValue* object = nullptr;
    switch(value.getType())
    {
    case Value::Type::MAP:
        object = new CCInnerValue(rapidjson::kObjectType);
        for (auto& iter: value.asValueMap())
        {
            auto iter_value = NDKHelper::GetJsonFromCCObject(iter.second, allocator);
            object->AddMember(iter.first.c_str(), 
                *static_cast<rapidjson::Value*>(iter_value),
                allocator);
        }
        break;
    case Value::Type::VECTOR:
        {
            object = new CCInnerValue(rapidjson::kArrayType);
            for (auto& iter: value.asValueVector())
            {
                object->PushBack(
                    *static_cast<rapidjson::Value*>(NDKHelper::GetJsonFromCCObject(iter, allocator)),
                    allocator);
            }
        }
        break;
    case Value::Type::STRING:
        {
            object = new CCInnerValue(value.asString().c_str(), allocator);
        }
        break;
    case Value::Type::FLOAT:
        {
            object = new CCInnerValue(value.asFloat());
        }
        break;
    case Value::Type::DOUBLE:
        {
            object = new CCInnerValue(value.asDouble());
        }
        break;
    case Value::Type::INTEGER:
    case Value::Type::BYTE:
        {
            object = new CCInnerValue(value.asInt());
        }
        break;
    case Value::Type::NONE:
    default:
        {
            object = new CCInnerValue();
        }
        break;
    }
    if (object)
    {
        object->autorelease();
    }
    return object;
}

void NDKHelper::PrintSelectorList()
{
    for (unsigned int i = 0; i < NDKHelper::selectorList.size(); ++i)
    {
        std::string s = NDKHelper::selectorList[i].getGroup();
        s.append(NDKHelper::selectorList[i].getName());
        CCLOG("%s",s.c_str());
    }
}

void NDKHelper::HandleMessage(const rapidjson::Value& methodName, const rapidjson::Value& methodParams)
{
    if (methodName.IsNull())
    {
        CCLOG("methodName is null");
        return;
    }

    const char *methodNameStr = methodName.GetString();
    NDKfunc *sel = nullptr;
    Value   *val = nullptr;
    for (unsigned int i = 0; i < NDKHelper::selectorList.size(); ++i)
    {
        if (NDKHelper::selectorList[i].getName() == methodNameStr)
        {
            sel = new NDKfunc(NDKHelper::selectorList[i].getSelector());
            val = new Value(NDKHelper::GetCCObjectFromJson(methodParams));

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                auto prm 	= val;
                auto call	= sel;
                if (nullptr != sel || nullptr != prm)
                {
                    (*call)(*prm);
                }
                CC_SAFE_DELETE(prm);
                CC_SAFE_DELETE(call);
           });
            break;
        }
    }
}
//#define CC_TARGET_PLATFORM CC_PLATFORM_ANDROID
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "android/jni/JniHelper.h"
    //#include <jni.h>

    #define CLASS_NAME "com/easyndk/classes/AndroidNDKHelper"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #import "IOSNDKHelper-C-Interface.h"
#endif

extern "C"
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Method for recieving NDK messages from Java, Android
    void Java_com_easyndk_classes_AndroidNDKHelper_CPPNativeCallHandler(JNIEnv* env, jobject thiz, jstring json)
    {
        std::string jsonString = JniHelper::jstring2string(json);

        rapidjson::Document d;
        d.Parse<0>(jsonString.c_str());
        if (d.HasParseError())  //¥Ú”°Ω‚Œˆ¥ÌŒÛ
        {
            CCLOG("GetParseError %s\n",d.GetParseError());
            return ;
        }
        CCLOG("jsonString :%s", jsonString.c_str());
        //rapidjson::Value *jsonMethodName, *jsonMethodParams;

        if (d.IsObject() && d.HasMember(__CALLED_METHOD__)) 
        {
            rapidjson::Value& jsonMethodName = d[__CALLED_METHOD__];
            if (d.HasMember(__CALLED_METHOD_PARAMS__)) 
            {
                //rapidjson::Value& jsonMethodParams = ;
                NDKHelper::HandleMessage(jsonMethodName, d[__CALLED_METHOD_PARAMS__]);
            }
            else
            {
                rapidjson::Value jsonMethodParams;
                NDKHelper::HandleMessage(jsonMethodName, jsonMethodParams);
            }
        }
        
        
        // Just to see on the log screen if messages are propogating properly
        //CCLOG("%s",jsonCharArray);
        //CCLOG("RecvMessage %s ", json_dumps(root, JSON_COMPACT | JSON_ENSURE_ASCII));
        
        //json_decref(root);
    }
    #endif
    
    // Method for sending message from CPP to the targetted platform
    void SendMessageWithParams(std::string methodName, const cocos2d::Value& methodParams)
    {
        if (methodName.empty())
            return;

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        document.AddMember(__CALLED_METHOD__, methodName.c_str(), allocator);
        

        auto Params = NDKHelper::GetJsonFromCCObject(methodParams, allocator);
        document.AddMember(__CALLED_METHOD_PARAMS__,
            *static_cast<rapidjson::Value*>(Params),
            allocator);
        

 
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo t;
        
		if (JniHelper::getStaticMethodInfo(t,
                                           CLASS_NAME,
                                           "RecieveCppMessage",
                                           "(Ljava/lang/String;)V"))
		{

            rapidjson::StringBuffer jsonStr;
            rapidjson::Writer<rapidjson::StringBuffer> writer(jsonStr);
            document.Accept(writer);

            CCLOG("SendMessage %s", jsonStr.GetString());
            jstring stringArg1 = t.env->NewStringUTF(jsonStr.GetString());
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
            t.env->DeleteLocalRef(stringArg1);
			t.env->DeleteLocalRef(t.classID);
		}
        #endif
        
        //json_decref(toBeSentJson);
    }
}
