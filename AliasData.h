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
#include <memory>

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
   COL_ID = 0,
   COL_TYPE,
   COL_NAME,
   COL_VALUE,
   NUM_COLS
 };
  
class AliasData {
public:
    AliasData(
        const unsigned id,
        std::string name, 
        AliasType type, 
        std::list<std::string> values);
    ~AliasData();
    
    inline AliasType GetType() { return mType; }
    inline std::string GetName() { return mName; }
    std::list<std::string> GetValues() { return mValues; }
    inline void SetName(std::string name) { mName = name; }
    inline void SetType(AliasType type) { mType = type; }
    void SetValues(std::list<std::string> val) { mValues = val; }
    void SetComment(std::list<std::string> val) { mComment = val; }
    void AppendComment(std::string val) { mComment.push_back(val); }
    std::list<std::string> GetComment() { return mComment; }
    std::string GetCommentAsString();
    std::string GetValuesString();
    std::string GetTypeString();
    std::string GetTypeToFile();
    
    const unsigned mId;
    
private:
    std::string mName;
    AliasType mType;
    std::list<std::string> mValues;
    std::list<std::string> mComment;

};

#endif /* ALIASDATA_H */

