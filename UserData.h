/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserData.h
 * Author: sssililliths
 *
 */

#ifndef USERDATA_H
#define USERDATA_H

#include <string>
#include <list>
#include <sstream>
#include <memory>


 enum class UserCols
 {
    COL_ID = 0,
    COL_NAME,
    COL_LOCATION,
    COL_RUNAS,
    COL_CMDS,
    COL_IS_GROUP,
    COL_IS_SYS_GROUP,
    NUM_COLS
 };
  
 
class UserData {
public:
    UserData(
        const unsigned id,
        std::string name, 
        std::string location, 
        std::string runas,
        std::list<std::string> cmds);
    ~UserData();
    
    std::string GetCmdsString();
    std::list<std::string> GetCmds() { return mCommands; };
    std::string GetLocation() { return mTerminals; };
    std::string GetName() { return mName; }
    std::string GetRunas() { return mAs; }
    bool IsGroup() { return mGroup; }
    bool IsSysGroup() { return mSystemGroup; }
    
    void SetComment(std::list<std::string> val) { mComment = val; }
    void AppendComment(std::string val) { mComment.push_back(val); }
    std::list<std::string> GetComment() { return mComment; }
    std::string GetCommentAsString();
    void SetCmdsString(std::list<std::string> cmds) { mCommands = cmds; };
    void SetName(std::string name) { mName = name; };
    void SetLocation(std::string location) { mTerminals = location; };
    void SetRunas(std::string runas) { mAs = runas; }
    void SetAsGroup() { mGroup = true; }
    void SetAsSystemGroup() { mGroup = true; mSystemGroup = true; }
    
    const unsigned mId;
    
private:
    std::string mName;
    std::list<std::string> mCommands;
    std::string mTerminals;
    std::string mAs;
    std::list<std::string> mComment;
    bool mGroup;
    bool mSystemGroup;

};

#endif /* USERDATA_H */

