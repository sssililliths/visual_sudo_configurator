/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AliasData.h
 * Author: sssililliths
 *
 */

#ifndef ALIASDATA_H
#define ALIASDATA_H

#include <string>
#include <list>

enum class AliasType
{
    USER_ALIAS,
    RUNAS_ALIAS,
    HOST_ALIAS,
    CMDS_ALIAS
};

class AliasData {
public:
    AliasData(std::string name, AliasType type, std::list<std::string> values);
    ~AliasData();
    
    inline AliasType GetType() { return mType; }
    inline std::string GetName() { return mName; }
    std::string GetValuesString();
    std::string GetTypeString();
    
private:
    std::string mName;
    AliasType mType;
    std::list<std::string> mValues;

};

#endif /* ALIASDATA_H */

