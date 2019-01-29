/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsData.h
 * Author: root
 *
 */

#ifndef DEFAULTSDATA_H
#define DEFAULTSDATA_H

#include <string>
#include <list>
#include "DefaultsParams.h"

enum class DefaultsType
{
    ALL_DEFAULTS,
    USER_DEFAULTS,
    RUNAS_DEFAULTS,
    HOST_DEFAULTS,
    CMDS_DEFAULTS,
    NUM_TYPES
};


 enum class DefaultsCols
 {
   COL_TYPE = 0,
   COL_OWNER,
   COL_PARAM,
   COL_VALUE,
   NUM_COLS
 };
  
class DefaultsData {
public:
    DefaultsData(
        DefaultsType type, 
        DefaultsParams param,
        std::string values,
        std::string owner = "");
    ~DefaultsData();
    
    inline DefaultsType GetType() { return mType; }
    std::string GetValues() { return mValues; }
    inline void SetType(DefaultsType type) { mType = type; }
    void SetValues(std::string val) { mValues = val; }
    void SetOwner(std::string owner) { mOwner = owner; }
    std::string GetOwner() { return mOwner; }
    DefaultsParams GetParam() { return mParam; }
    std::string GetValuesString();
    std::string GetTypeString();
    std::string GetTypeToFile();
    
private:
    DefaultsType mType;
    std::string mValues;
    std::string mOwner;
    DefaultsParams mParam;

};

inline
DefaultsType GetTypeFromName(std::string name)
{
    const char *defaultsTypes[] = { "", "USER", "RUNAS", "HOST", "CMDS"};
    for (int i = 0; i < static_cast<int>(DefaultsType::NUM_TYPES); i++)
    {
        if (std::string(defaultsTypes[i]) == name)
        {
            return static_cast<DefaultsType>(i);
        }
    }
    return DefaultsType::NUM_TYPES;
}
#endif /* DEFAULTSDATA_H */

