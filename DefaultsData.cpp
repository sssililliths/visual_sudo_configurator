/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsData.cpp
 * Author: root
 * 
 */

#include "DefaultsData.h"
#include <sstream>

DefaultsData::DefaultsData(
    const unsigned id,
    DefaultsType type, 
    DefaultsParams param,
    std::string values,
    std::string owner) :
        mId(id),
        mParam(param),
        mType(type),
        mValues(values),
        mOwner(owner)
{
}

DefaultsData::~DefaultsData()
{
}

std::string DefaultsData::GetValuesString()
{
    return mValues;
}


std::string DefaultsData::GetTypeString()
{
    std::stringstream ss;
    switch(mType)
    {
    case DefaultsType::USER_DEFAULTS:
        ss << "User";
        break;
    case DefaultsType::HOST_DEFAULTS:
        ss << "Host";
        break;
    case DefaultsType::RUNAS_DEFAULTS:
        ss << "Run as";
        break;
    case DefaultsType::CMDS_DEFAULTS:
        ss << "Cmnd";
        break;
    }
    
    return ss.str();
}


std::string DefaultsData::GetTypeToFile()
{
    std::stringstream ss;
    switch(mType)
    {
    case DefaultsType::USER_DEFAULTS:
        ss << ":";
        break;
    case DefaultsType::HOST_DEFAULTS:
        ss << "@";
        break;
    case DefaultsType::RUNAS_DEFAULTS:
        ss << ">";
        break;
    case DefaultsType::CMDS_DEFAULTS:
        ss << "!";
        break;
    }
    
    return ss.str();
}


std::string DefaultsData::GetCommentAsString()
{
    std::stringstream ss;
    
    for (std::string line : mComment)
    {
        ss << line << "\n";
    }
    
    return ss.str();
}
