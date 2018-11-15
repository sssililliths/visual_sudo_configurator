/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataManager.h
 * Author: sssililliths
 *
 */

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "AliasData.h"
#include "GroupData.h"
#include "UserData.h"


class DataManager {
public:
    static DataManager* getInstance();
    
    void AddAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values);    
    AliasData* GetAlias(std::string name);
    std::list<AliasData*> GetAliasesByValue(std::string value);
    std::list<AliasData*> GetAliasesByType(AliasType value);
    void ModifyAlias(std::string name);
    void RemoveAlias(std::string name);
    
    void AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds);
    UserData* GetUser(std::string name);
    std::list<UserData*> GetUsersByGroup(std::string name);
    void ModifyUser(std::string name);
    void RemoveUser(std::string name);
    
    void AddGroup(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool isSystemGroup);
    GroupData* GetGroupByName(std::string name);
    std::list<GroupData*> GetGroupsByUser(std::string name);
    std::list<GroupData*> GetGroupsByAlias(std::string name);
    void ModifyGroup(std::string name);
    void RemoveGroup(std::string name);
    
private:    
    DataManager();
    ~DataManager();
    
private:
    static DataManager* mInstance;
    
    std::list<AliasData*> mAliases;
    std::list<GroupData*> mGroups;
    std::list<UserData*> mUsers;
};

#endif /* DATAMANAGER_H */

