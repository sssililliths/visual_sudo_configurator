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


 enum class UserCols
 {
   COL_NAME = 0,
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
    
    void SetComment(std::string val) { mComment = val; }
    std::string GetComment() { return mComment; }
    void SetCmdsString(std::list<std::string> cmds) { mCommands = cmds; };
    void SetLocation(std::string location) { mTerminals = location; };
    void SetRunas(std::string runas) { mAs = runas; }
    void SetAsGroup() { mGroup = true; }
    void SetAsSystemGroup() { mGroup = true; mSystemGroup = true; }
    
private:
    std::string mName;
    std::list<std::string> mCommands;
    std::string mTerminals;
    std::string mAs;
    std::string mComment;
    bool mGroup;
    bool mSystemGroup;

};

#endif /* USERDATA_H */

