//
//  NDKCallbackNode.cpp
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//
//

#include "NDKCallbackNode.h"
USING_NS_CC;

NDKCallbackNode::NDKCallbackNode(const char *groupName, const char *name, NDKfunc &func)
{
    this->groupName = groupName;
    this->name = name;
    this->sel = func;
}

std::string NDKCallbackNode::getName()
{
    return this->name;
}

std::string NDKCallbackNode::getGroup()
{
    return this->groupName;
}

NDKfunc NDKCallbackNode::getSelector()
{
    return this->sel;
}