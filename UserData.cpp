/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserData.cpp
 * Author: sssililliths
 * 
 */

#include "UserData.h"

UserData::UserData(
    const unsigned id,
    std::string name, 
    std::string location, 
    std::string runas,
    std::list<std::string> cmds) :
        mId(id),
        mName(name),
        mTerminals(location),
        mAs(runas),
        mCommands(cmds),
        mGroup(false),
        mSystemGroup(false)
        
{
}

std::string UserData::GetCmdsString()
{    
    std::stringstream ss;
    for (std::string elem : mCommands)
    {
        ss << elem;
        
        if (mCommands.back() != elem)
        {
            ss << ", ";
        }
    }
    std::string result = ss.str();
    return result;
}


std::string UserData::GetCommentAsString()
{
    std::stringstream ss;
    
    for (std::string line : mComment)
    {
        ss << line << "\n";
    }
    
    return ss.str();
}


UserData::~UserData()
{
}

