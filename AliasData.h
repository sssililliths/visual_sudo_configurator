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
    CMDS_ALIAS,
    NUM_TYPES
};

 enum class AliasCols
 {
   COL_TYPE = 0,
   COL_NAME,
   COL_VALUE,
   NUM_COLS
 };
  
class AliasData {
public:
    AliasData(std::string name, AliasType type, std::list<std::string> values);
    ~AliasData();
    
    inline AliasType GetType() { return mType; }
    inline std::string GetName() { return mName; }
    std::list<std::string> GetValues() { return mValues; }
    inline void SetType(AliasType type) { mType = type; }
    void SetValues(std::list<std::string> val) { mValues = val; }
    void SetComment(std::string val) { mComment = val; }
    std::string GetComment() { return mComment; }
    std::string GetValuesString();
    std::string GetTypeString();
    std::string GetTypeToFile();
    
private:
    const std::string mName;
    AliasType mType;
    std::list<std::string> mValues;
    std::string mComment;

};

#endif /* ALIASDATA_H */

