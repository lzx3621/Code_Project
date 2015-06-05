//
//  NDKCallbackNode.h
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//
//

#ifndef __EasyNDK_for_cocos2dx__NDKCallbackNode__
#define __EasyNDK_for_cocos2dx__NDKCallbackNode__

#include "cocos2d.h"
//typedef cocos2d::SEL_CallFuncND NDKfunc;
typedef std::function<void(const cocos2d::Value&)> NDKfunc;
class NDKCallbackNode
{
    private :
    NDKfunc sel;
    std::string name;
    std::string groupName;
    
    public :
    NDKCallbackNode(const char *groupName, const char *name, NDKfunc &func);
    std::string getName();
    std::string getGroup();
    NDKfunc getSelector();
};

#endif /* defined(__EasyNDK_for_cocos2dx__NDKCallbackNode__) */
