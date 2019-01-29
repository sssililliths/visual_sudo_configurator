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
#include "DefaultsParams.h"


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
    
    std::list<AliasData*> DataManager::GetAliases()
    {
        return mAliases;
    }
    
    void DataManager::ModifyAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->GetName() == name)
            {
                elem->SetType(type);
                elem->SetValues(values);
                return;
            }
        }
    }
    
    void DataManager::SetAliasComment(std::string name, std::string comment)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->GetName() == name)
            {
                elem->SetComment(comment);
                return;
            }
        }
    }
    
    void DataManager::RemoveAlias(std::string name)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->GetName() == name)
            {
                mAliases.remove(elem);
                return;
            }
        }
    }
    
    void DataManager::AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool isGroup,
        bool isSystemGroup)
    {
        UserData* newUser = new UserData(
                                        name, 
                                        location, 
                                        runas,
                                        cmds);
        if (isSystemGroup)
        {
            newUser->SetAsSystemGroup();
        }
        else if (isGroup)
        {
            newUser->SetAsGroup();
        }
        
        mUsers.push_back(newUser);
    }
    
    UserData* DataManager::GetUser(std::string name)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->GetName() == name)
            {
                return elem;
            }
        }
        
        return NULL;
    }
    
    std::list<UserData*> DataManager::GetUsers()
    {
        return mUsers;
    }

    
    void DataManager::ModifyUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds)
    {        
        for (UserData* elem : mUsers)
        {
            if (elem->GetName() == name)
            {
                elem->SetLocation(location);
                elem->SetRunas(runas);
                elem->SetCmdsString(cmds);
                return;
            }
        }
    }
    
    void DataManager::RemoveUser(std::string name)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->GetName() == name)
            {
                mUsers.remove(elem);
                return;
            }
        }
    }            
    
    void DataManager::SetUserComment(std::string name, std::string comment)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->GetName() == name)
            {
                elem->SetComment(comment);
                return;
            }
        }
    }
    
    
    void DataManager::AddDefaults(
        DefaultsType type, 
        std::string owner,
        std::string param,
        std::string values)
    {
        DefaultsData* defaults = NULL;
        DefaultsParams params;
        for(long i = 0; i < static_cast<long>(DefaultsParams::NUM_OF_PARAMS); i++)
        {
            if(param == g_DefaultsParamNames[i])
            {
                params = static_cast<DefaultsParams>(i);
                break;
            }
        }
        
        defaults = new DefaultsData(type, params, values, owner);
        mDefaults.push_back(defaults);
    }
    
    
    DefaultsData* DataManager::GetDefaults(DefaultsType type, DefaultsParams param)
    {
        for(DefaultsData* elem : mDefaults)
        {
            if (elem->GetType() == type && elem->GetParam() == param)
            {
                return elem;
            }
        }
        
        return NULL;
    }
    
    std::list<DefaultsData*> DataManager::GetDefaultses()
    {
        return mDefaults;
    }
    
    void DataManager::ModifyDefaults(
        DefaultsType type, 
        std::string owner,
        DefaultsParams param,
        std::string values)
    {
        for(DefaultsData* elem : mDefaults)
        {
            if (elem->GetType() == type && elem->GetParam() == param)
            {
                elem->SetOwner(owner);
                elem->SetValues(values);
            }
        }
    }
    
    void DataManager::RemoveDefaults(DefaultsType type, DefaultsParams param, std::string owner)
    {
        for (DefaultsData* elem : mDefaults)
        {
            if (elem->GetType() == type &&
                elem->GetParam() == param &&
                elem->GetOwner() == owner)
            {
                mDefaults.remove(elem);
                return;
            }
        }
    }
    