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
#include "UserData.h"
#include "DefaultsData.h"


class DataManager {
public:
    static DataManager* getInstance();
    
    void AddAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values);    
    AliasData* GetAlias(std::string name);
    std::list<AliasData*> GetAliasesByValue(std::string value);
    std::list<AliasData*> GetAliases();
    void ModifyAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values);
    void RemoveAlias(std::string name);
    void SetAliasComment(std::string name, std::string comment);
    
    void AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool isGroup,
        bool isSystemGroup = false);
    UserData* GetUser(std::string name);
    std::list<UserData*> GetUsers();
    void ModifyUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds);
    void RemoveUser(std::string name);
    void SetUserComment(std::string name, std::string comment);
    
    void AddDefaults(
        DefaultsType type, 
        std::string owner,
        std::string param,
        std::string values);    
    DefaultsData* GetDefaults(DefaultsType type, DefaultsParams param);
    std::list<DefaultsData*> GetDefaultses();
    void ModifyDefaults(
        DefaultsType type, 
        std::string owner,
        DefaultsParams param,
        std::string values);
    void RemoveDefaults(DefaultsType type, DefaultsParams param, std::string owner);
    
private:    
    DataManager();
    ~DataManager();
    
private:
    static DataManager* mInstance;
    
    std::list<AliasData*> mAliases;
    std::list<UserData*> mUsers;
    std::list<DefaultsData*> mDefaults;
};

#endif /* DATAMANAGER_H */

