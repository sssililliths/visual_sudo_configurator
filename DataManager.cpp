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

#include <iterator>
#include "DataManager.h"
#include "DefaultsParams.h"


DataManager* DataManager::mInstance = 0;


std::list<std::string> Split(std::string str, std::string delim)
{
    size_t pos = 0;
    std::string tmp;
    std::list<std::string> result;
    while ((pos = str.find(delim)) != std::string::npos) 
    {
        tmp = str.substr(0, pos);
        str.erase(0, pos + delim.length());
        result.push_back(tmp);
    }
    
    if (!str.empty())
    {
        result.push_back(str);
    }
    
    return result;
}

//------------------------------------------------------------------------------

DataManager::DataManager() :
    mChanged(false)
{
}

//------------------------------------------------------------------------------

DataManager::~DataManager()
{
    if (mInstance)
    {
        mInstance = NULL;
    }
}

//------------------------------------------------------------------------------

DataManager* DataManager::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new DataManager();
    }

    return mInstance;
}

//------------------------------------------------------------------------------

std::string DataManager::GetMainCommentStr()
{
    std::stringstream ss;
    
    for (std::string line : mMainComment)
    {
        ss << line
           << "\n";
    }
    
    return ss.str();
}

//------------------------------------------------------------------------------

void DataManager::SetMainComment(std::string val)
{
    mMainComment = Split(val, "\n");
}

/******************************************************************************\
 *                                 Aliases
 \*****************************************************************************/

    unsigned DataManager::GetAliasId()
    {
        if (mAliases.empty())
        {
            return 1;
        }
        else
        {
            return mAliases.back()->mId+1;
        }
    }

//------------------------------------------------------------------------------

    void DataManager::AddAlias(
        std::string name, 
        AliasType type, 
        std::list<std::string> values,
        bool fromParser = false)
    {
        mChanged = !fromParser;
        AliasData* newAlias = new AliasData(GetAliasId(), name, type, values);
        mAliases.push_back(newAlias);
    }
   
//------------------------------------------------------------------------------   
    
    AliasData* DataManager::GetAlias(unsigned id)
    {
        std::list<AliasData*>  typeAliases = {};
        for (AliasData* elem : mAliases)
        {
            if (elem->mId == id)
            {
                return elem;
            }
        }
        
        return NULL;
    }
   
//------------------------------------------------------------------------------   
    
    AliasData* DataManager::GetAliasByName(std::string name)
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
        
//------------------------------------------------------------------------------
    
    std::list<AliasData*> DataManager::GetAliases()
    {
        return mAliases;
    }
    
//------------------------------------------------------------------------------
    
    void DataManager::ModifyAlias(
        unsigned id,
        std::string name, 
        AliasType type, 
        std::list<std::string> values)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->mId == id)
            {
                mChanged = true;
                elem->SetName(name);
                elem->SetType(type);
                elem->SetValues(values);
                return;
            }
        }
    }
    
//------------------------------------------------------------------------------
    
    void DataManager::SetAliasComment(
                                unsigned id, 
                                std::string comment, 
                                bool fromParser)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->mId == id)
            {
                mChanged = !fromParser;
                elem->SetComment(Split(comment, "\n"));
                return;
            }
        }
    }
    
//------------------------------------------------------------------------------
    
    void DataManager::RemoveAlias(unsigned id)
    {
        for (AliasData* elem : mAliases)
        {
            if (elem->mId == id)
            {
                mChanged = true;
                mAliases.remove(elem);
                return;
            }
        }
    }
    
    
/******************************************************************************\
 *                                 Users
 \*****************************************************************************/
    
    unsigned DataManager::GetUserId()
    {
        if (mUsers.empty())
        {
            return 1;
        }
        else
        {
            return mUsers.back()->mId+1;
        }
    }

//------------------------------------------------------------------------------
    
    void DataManager::AddUser(
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds,
        bool fromParser,
        bool isGroup,
        bool isSystemGroup)
    {
        UserData* newUser = new UserData(
                                        GetUserId(),
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
        
        mChanged = !fromParser;
        mUsers.push_back(newUser);
    }
    
//------------------------------------------------------------------------------
    
    UserData* DataManager::GetUser(unsigned id)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->mId == id)
            {
                return elem;
            }
        }
        
        return NULL;
    }
    
//------------------------------------------------------------------------------
    
    std::list<UserData*> DataManager::GetUsers()
    {
        return mUsers;
    }

//------------------------------------------------------------------------------
    
    void DataManager::ModifyUser(
        unsigned id,
        std::string name, 
        std::string location, 
        std::string runas, 
        std::list<std::string> cmds)
    {        
        for (UserData* elem : mUsers)
        {
            if (elem->mId == id)
            {
                mChanged = true;
                elem->SetName(name);
                elem->SetLocation(location);
                elem->SetRunas(runas);
                elem->SetCmdsString(cmds);
                return;
            }
        }
    }
    
//------------------------------------------------------------------------------
    
    void DataManager::RemoveUser(unsigned id)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->mId == id)
            {
                mChanged = true;
                mUsers.remove(elem);
                return;
            }
        }
    }            
    
//------------------------------------------------------------------------------
    
    void DataManager::SetUserComment(
                                unsigned id, 
                                std::string comment,
                                bool fromParser)
    {
        for (UserData* elem : mUsers)
        {
            if (elem->mId == id)
            {
                mChanged = !fromParser;
                elem->SetComment(Split(comment, "\n"));
                return;
            }
        }
    }
    
    
/******************************************************************************\
 *                                 Defaults
 \*****************************************************************************/
    
    unsigned DataManager::GetDefaultsId()
    {
        if (mDefaults.empty())
        {
            return 1;
        }
        else
        {
            return mDefaults.back()->mId+1;
        }
    }

//------------------------------------------------------------------------------
    
    void DataManager::AddDefaults(
        DefaultsType type, 
        std::string owner,
        std::string param,
        std::string values,
        DefaultsSign sign,
        bool fromParser)
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
        
        mChanged = !fromParser;
        defaults = new DefaultsData(GetDefaultsId(), type, params, values, owner, sign);
        mDefaults.push_back(defaults);
    }
  
//------------------------------------------------------------------------------  
    
    DefaultsData* DataManager::GetDefaults(unsigned id)
    {
        for(DefaultsData* elem : mDefaults)
        {
            if (elem->mId == id)
            {
                return elem;
            }
        }
        
        return NULL;
    }
    
//------------------------------------------------------------------------------
    
    std::list<DefaultsData*> DataManager::GetDefaultses()
    {
        return mDefaults;
    }
    
    void DataManager::ModifyDefaults(
        unsigned id,
        DefaultsType type, 
        std::string owner,
        DefaultsParams param,
        std::string values,
        DefaultsSign sign)
    {
        for(DefaultsData* elem : mDefaults)
        {
            if (elem->mId == id)
            {
                mChanged = true;
                elem->SetType(type);
                elem->SetOwner(owner);
                elem->SetParam(param);
                elem->SetValues(values);
                elem->SetSign(sign);
            }
        }
    }
    
//------------------------------------------------------------------------------
    
    void DataManager::RemoveDefaults(unsigned id)
    {
        for (DefaultsData* elem : mDefaults)
        {
            if (elem->mId == id)
            {
                mDefaults.remove(elem);
                mChanged = true;
                return;
            }
        }
    } 
    
//------------------------------------------------------------------------------
    
    void DataManager::SetDefaultsComment(
                                unsigned id, 
                                std::string comment,
                                bool fromParser)
    {
        for (DefaultsData* elem : mDefaults)
        {
            if (elem->mId == id)
            {
                mChanged = !fromParser;
                elem->SetComment(Split(comment, "\n"));
                return;
            }
        }
    }
    
    
template <typename T>
T GetElementById(std::list<T> l, unsigned id)
{
    typename std::list<T>::iterator it = std::next(l.begin(), id-1);
    
    do
    {
        unsigned currElemId = *it->mId;
        
        if (currElemId == id)
            return *it;
        
        if ((currElemId > id && it == l.begin()) ||
            (currElemId < id && it == l.end()))
            return NULL;
        
        unsigned prevElemId = *(it-1)->mId;
        unsigned nextElemId = *(it+1)->mId;
        
        if ((currElemId > id && prevElemId < id) ||
            (currElemId < id && nextElemId > id))
           return NULL; 
        
        if (currElemId < id) it++;
        else it--;
    }
    while(true);
    
}
