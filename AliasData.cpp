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
    std::string name, 
    AliasType type, 
    std::list<std::string> values) :
        mName(name),
        mType(type),
        mValues(values)
{
}

AliasData::~AliasData()
{
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
    
    return ss.str();
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
