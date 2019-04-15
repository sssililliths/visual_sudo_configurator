/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AliasData.cpp
 * Author: sssililliths
 * 
 */

#include "AliasData.h"
#include <sstream>

AliasData::AliasData(
    const unsigned id,
    std::string name, 
    AliasType type, 
    std::list<std::string> values) :
        mId(id),
        mName(name),
        mType(type),
        mValues(values)
{
}

AliasData::~AliasData()
{
    mValues.clear();
}

std::string AliasData::GetValuesString()
{
    std::stringstream ss;
    for (std::string elem : mValues)
    {
        ss << elem;
        
        if (mValues.back() != elem)
        {
            ss << ", ";
        }
    }
    std::string result = ss.str();
    return result;
}


std::string AliasData::GetTypeString()
{
    std::stringstream ss;
    switch(mType)
    {
    case AliasType::USER_ALIAS:
        ss << "User";
        break;
    case AliasType::HOST_ALIAS:
        ss << "Host";
        break;
    case AliasType::RUNAS_ALIAS:
        ss << "Run as";
        break;
    case AliasType::CMDS_ALIAS:
        ss << "Cmnd";
        break;
    }
    
    return ss.str();
}


std::string AliasData::GetTypeToFile()
{
    std::stringstream ss;
    switch(mType)
    {
    case AliasType::USER_ALIAS:
        ss << "User_Alias";
        break;
    case AliasType::HOST_ALIAS:
        ss << "Host_Alias";
        break;
    case AliasType::RUNAS_ALIAS:
        ss << "Runas_Alias";
        break;
    case AliasType::CMDS_ALIAS:
        ss << "Cmds_Alias";
        break;
    }
    
    return ss.str();
}


std::string AliasData::GetCommentAsString()
{
    std::stringstream ss;
    
    for (std::string line : mComment)
    {
        ss << line << "\n";
    }
    
    return ss.str();
}
