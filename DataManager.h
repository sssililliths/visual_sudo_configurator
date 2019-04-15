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
    ~DataManager();
    static DataManager* getInstance();
    bool Changed() { return mChanged; }
    
    // Aliases:
    void AddAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values,
        bool fromParser);    
    AliasData* GetAlias(unsigned id);
    AliasData* GetAliasByName(std::string name);
    std::list<AliasData*> GetAliases();
    
    void ModifyAlias(
        unsigned id,
        std::string name, 
        AliasType type, 
        std::list<std::string> values);
    
    void RemoveAlias(unsigned id);
    
    void SetAliasComment(
                    unsigned id, 
                    std::string comment, 
                    bool fromParser);
    
    AliasData* GetLastAlias() { return mAliases.back(); }
    
    unsigned GetAliasId();
    
    // Users:
    void AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool fromParser,
        bool isGroup,
        bool isSystemGroup = false);
    
    UserData* GetUser(unsigned id);
    
    std::list<UserData*> GetUsers();
    
    void ModifyUser(
        unsigned id,
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds);
    
    void RemoveUser(unsigned id);
    
    void SetUserComment(
                    unsigned id, 
                    std::string comment,
                    bool fromParser);
    
    UserData* GetLastUser() { return mUsers.back(); }    
    
    unsigned GetUserId();
    
    // Defaults:
    void AddDefaults(
        DefaultsType type, 
        std::string owner,
        std::string param,
        std::string values,
        bool fromParser);    
    
    DefaultsData* GetDefaults(unsigned id);
    
    std::list<DefaultsData*> GetDefaultses();
    
    void ModifyDefaults(
        unsigned id,
        DefaultsType type, 
        std::string owner,
        DefaultsParams param,
        std::string values);
    
    void RemoveDefaults(unsigned id);
    
    void SetDefaultsComment(
                        unsigned id, 
                        std::string comment,
                        bool fromParser);
    
    DefaultsData* GetLastDefaults() { return mDefaults.back(); }
    
    unsigned GetDefaultsId();
    
    void SetMainComment(std::list<std::string> val) { mMainComment = val; }
    void SetMainComment(std::string val);
    void AppendMainComment(std::string val) { mMainComment.push_back(val); }
    std::list<std::string> GetMainComment() { return mMainComment; }
    std::string GetMainCommentStr();
    
    void AppendIncludedir(std::string val) { mIncludedirs.push_back(val); }
    void AppendInclude(std::string val) { mIncludes.push_back(val); }
    std::list<std::string> GetIncludes() { return mIncludes; }
    std::list<std::string> GetIncludedirs() { return mIncludedirs; }
    
private:    
    DataManager();
    
private:
    static DataManager* mInstance;
    
    std::list<std::string> mMainComment;
    std::list<AliasData*> mAliases;
    std::list<UserData*> mUsers;
    std::list<DefaultsData*> mDefaults;
    std::list<std::string> mIncludedirs;
    std::list<std::string> mIncludes;    
    
    bool mChanged;
};

#endif /* DATAMANAGER_H */

