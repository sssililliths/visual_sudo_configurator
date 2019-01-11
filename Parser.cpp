/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: sssililliths
 * 
 */


#include "Parser.h"
#include "DataManager.h"
#include <algorithm> 
#include <sstream>

Parser* Parser::mInstance = 0;

Parser::Parser() 
{}

Parser* Parser::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new Parser();
    }

    return mInstance;
}

void Parser::ParseLine(std::string line)
{
    if (line.empty()) return;
    DataManager* dm = DataManager::getInstance();
    
    std::vector<std::string> lineData = Split(line);
    
    if(ToLower(lineData[0]).find("_alias") != std::string::npos) // aliases
    {
        ParseAlias(lineData);
        mLastParsedType = LastElement::LINE_ALIAS;
    } 
    else if (lineData[0][0] == '%' || 
            (dm->GetAlias(lineData[0]) != NULL && dm->GetAlias(lineData[0])->GetType() == AliasType::USER_ALIAS)) // groups
    {
        ParseUser<true>(lineData);
        mLastParsedType = LastElement::LINE_USER;
    }
    else if (lineData[0][0] == '#')
    {
        std::stringstream ss;
        for (std::string word : lineData)
            ss << word << " ";
        std::string tmp = ss.str();
        tmp = tmp.substr (1,tmp.length()-1);
        if (tmp[0] == ' ')
        {
            tmp = tmp.substr (1,tmp.length()-1);
        }
        
        if (mLastParsedType == LastElement::LINE_ALIAS)
        {
            mLastAlias->SetComment(tmp);
        }
        else
        {
            mLastUser->SetComment(tmp);
        }
    }
    else
    {
        ParseUser<false>(lineData);
        mLastParsedType = LastElement::LINE_USER;
    }    
}

template<bool isGroup>
void Parser::ParseUser(std::vector<std::string> userData)
{
    /*
     * group_name location=(optional_as) cmds
     *    [0]            [1]             [2+]
     * 
     * group_name location= (optional_as) cmds
     *    [0]       [1]         [2]       [3+]
     * 
     * group_name location = (optional_as) cmds
     *    [0]        [1]  [2]     [3]      [4]
     * 
     * group_name location= (optional_as) cmds
     *    [0]       [1]         [2]       [3+]
     */
    unsigned currentElement = 0;
    bool isSystemGroup = userData[0][0] == '%';
    if (isGroup)
    {
        if(isSystemGroup)
        {
            userData[currentElement].substr(1, userData[currentElement].size()); // we don't need to have this symbol in name
        }    
    }
    
    std::string name = userData[currentElement];
    std::string location = "";
    std::string runAs = "";
    std::list<std::string> cmds; 
    currentElement++; // we can now safe parse next element
    
    // check group where=(as) cmd, group where= (as) cmd, group where=cmd and group where= cmd
    // currentElement is 1
    if (userData[currentElement].find("=") != std::string::npos)
    {
        // group where= ..., just remove =
        if(userData[currentElement].back() == '=')
        {
            location = userData[currentElement].substr(0, userData[currentElement].size() - 1);
            currentElement++;
            
            if(userData[currentElement].find("(") != std::string::npos) // next we have runas
            {
                runAs = userData[currentElement].substr(1, userData[currentElement].size() - 2); // remove ()
                currentElement++;
            }
            // currentElement may be different, but we have only commands
        }
        else // group where=(as) cmd or group where=cmd
        {
            std::vector<std::string> tmp = Split(userData[currentElement], "=");
            location = tmp[0];
            
            if(tmp[1].find("(") != std::string::npos) // next we have runas
            {
                runAs = tmp[1].substr(1, tmp[1].size() - 2);
                currentElement++;
            }
            else
            {
                userData[currentElement] = tmp[1]; 
                // put command to main data vector; current won't be necessary now, but don't increment currentElement
            }
            // currentElement may be different, but we have only commands
        }
    }
    else
    {
        location = userData[currentElement];
        currentElement++;
        if (userData[currentElement] == "=")
        {
            currentElement ++; // skip = in group where = (as) cmds or group where = cmds
        }
        else // creepy, group where =sth
        {
            // remove first char (=)
            userData[currentElement] = userData[currentElement].substr(1, userData[currentElement].size());
        }
        
        if(userData[currentElement].find("(") != std::string::npos) // next we have runas
        {
            runAs = userData[currentElement].substr(1, userData[currentElement].size() - 2);
            currentElement++;
        }
        // currentElement may be different, but we have only commands
    }
    
    // iterate commands and add to vec
    for(int i = currentElement; i < userData.size(); i++)
    {
        std::string tmp = userData[i];
        if (tmp[tmp.length()-1] == ',')
        {
            tmp = tmp.substr(0, tmp.length()-1);
        }
        cmds.push_back(tmp);
    }
    
    DataManager::getInstance()->AddUser(name, location, runAs, cmds, isGroup, isSystemGroup);
    mLastUser = DataManager::getInstance()->GetUser(name);
}

void Parser::ParseAlias(std::vector<std::string> aliasData)
{
    AliasType aliasType = GetAliasType(aliasData[0]);
    std::string aliasName = aliasData[1];
    std::list<std::string> aliasValues = {};
    
    for (int i = 3; i < aliasData.size(); i++)
    {
        std::string tmp = aliasData[i];
        if (tmp[tmp.length()-1] == ',')
        {
            tmp = tmp.substr(0, tmp.length()-1);
        }
        aliasValues.push_back(tmp);
    }
    
    DataManager::getInstance()->AddAlias(aliasName, aliasType, aliasValues);
    mLastAlias = DataManager::getInstance()->GetAlias(aliasName);
}

AliasType Parser::GetAliasType(std::string str)
{
    std::string type = ToLower(str);
    if(type == "user_alias")
    {
        return AliasType::USER_ALIAS;
    }
    else if(type == "runas_alias")
    {
        return AliasType::RUNAS_ALIAS;
    }
    else if(type == "host_alias")
    {
        return AliasType::HOST_ALIAS;
    }
    else //if(ToLower(str) == "cmnd_alias")
    {
        return AliasType::CMDS_ALIAS;
    }
}

std::string Parser::ToLower(std::string str)
{
    std::stringstream ss;
    
    for (char c : str)
    {
        if (('A' <= c) && ( c <= 'Z'))
        {
            ss << (char)(c -('Z' - 'z'));
        }
        else
        {
            ss << c;
        }
    }
    return ss.str();
}

std::vector<std::string> Parser::Split(std::string str, std::string delim)
{
    size_t pos = 0;
    std::string tmp;
    std::vector<std::string> result;
    while ((pos = str.find(delim)) != std::string::npos) 
    {
        tmp = str.substr(0, pos);
        str.erase(0, pos + delim.length());
        if (tmp.empty()) continue;
        result.push_back(tmp);
    }
    
    if (!str.empty())
    {
        result.push_back(str);
    }
    
    return result;
}


    std::string Parser::PrepareToSave()
    {
        std::stringstream ss;
        
        for (AliasData* alias : DataManager::getInstance()->GetAliases())
        {
            ss << alias->GetTypeToFile() << " "
               << alias->GetName() << " = "
               << alias->GetValuesString() << std::endl;
            
            if (!alias->GetComment().empty())
            {
                ss << "# " << alias->GetComment() << std::endl
                        << std::endl;
            }
        }
        
        ss << std::endl << std::endl;
        
        for (UserData* user : DataManager::getInstance()->GetUsers())
        {
            ss << user->GetName() << " "
               << user->GetLocation() << "=";
            
            if(!user->GetRunas().empty())
            {
                ss << "(" << user->GetRunas() << ") ";
            }
            else
            {
                ss << " ";
            }
            
            ss << user->GetCmdsString() << std::endl;
            ss << std::endl; 
            
            if (!user->GetComment().empty())
            {
                ss << "# " << user->GetComment() << std::endl 
                        << std::endl;
            }
        }
        
        return ss.str();
    }
    
