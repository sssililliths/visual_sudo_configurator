/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataManager.cpp
 * Author: sssililliths
 * 
 */

#include "DataManager.h"


DataManager* DataManager::mInstance = 0;

DataManager::DataManager() :
    mAliases({})
{
}

DataManager::~DataManager()
{
}

DataManager* DataManager::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new DataManager();
    }

    return mInstance;
}

    void DataManager::AddAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values)
    {
        AliasData* newAlias = new AliasData(name, type, values);
        mAliases.push_back(newAlias);
    }
    
    AliasData* DataManager::GetAlias(std::string name)
    {
        std::list<AliasData*>  typeAliases = {};
        for (AliasData* elem : mAliases)
        {
            if (elem->GetName() == name)
            {
                return elem;
            }
        }
        
        return NULL;
    }
    
    std::list<AliasData*> DataManager::GetAliasesByValue(std::string value)
    {
        // todo find aliases by val and return it
        return mAliases;
    }
    
    std::list<AliasData*> DataManager::GetAliasesByType(AliasType value)
    {
        std::list<AliasData*>  typeAliases = {};
        for (AliasData* elem : mAliases)
        {
            if (elem->GetType() == value)
            {
                typeAliases.push_back(elem);
            }
        }
        
        return typeAliases;
    }
    
    void DataManager::ModifyAlias(std::string name)
    {}
    
    void DataManager::RemoveAlias(std::string name)
    {}
    
    void DataManager::AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds)
    {}
    
    UserData* DataManager::GetUser(std::string name)
    {
        // todo find user by name and return it
        return NULL;
    }
    
    std::list<UserData*> DataManager::GetUsersByGroup(std::string name)
    {
        // todo find users by group and return it
        return mUsers;
    }
    
    void DataManager::ModifyUser(std::string name)
    {}
    
    void DataManager::RemoveUser(std::string name)
    {}
    
    void DataManager::AddGroup(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool isSystemGroup)
    {}
    
    GroupData* DataManager::GetGroupByName(std::string name)
    {
        // todo find group by name and return it
        return NULL;
    }
    
    std::list<GroupData*> DataManager::GetGroupsByUser(std::string name)
    {
        // todo find groups by user and return it
        return mGroups;
    }
    
    std::list<GroupData*> DataManager::GetGroupsByAlias(std::string name)
    {
        // todo find groups by alias ( alias != name ? ) and return it
        return mGroups;
    }
    
    void DataManager::ModifyGroup(std::string name)
    {}
    
    void DataManager::RemoveGroup(std::string name)
    {}