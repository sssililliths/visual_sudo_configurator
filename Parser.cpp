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
#include "DefaultsParams.h"
#include <algorithm> 
#include <sstream>


void ReplaceAll(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}


Parser* Parser::mInstance = 0;

//------------------------------------------------------------------------------

Parser::Parser() :
    mLastUser(NULL),
    mLastAlias(NULL),
    mMainComment(""),
    mContinue(false),
    mNextLine(false)
{}

//------------------------------------------------------------------------------

Parser* Parser::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new Parser();
    }

    return mInstance;
}

//------------------------------------------------------------------------------

std::string Parser::ParseLine(std::string line, unsigned cnt)
{
    std::string error = "";
    ReplaceAll(line, "\t", "    ");
    ReplaceAll(line, "\r", "");
    if (line.empty() 
     || line.find_first_not_of(' ') == std::string::npos) 
        return "";
        
    std::vector<std::string> lineData = Split(line);
    if (!mContinue)
    {    
        if(ToLower(lineData[0]).find("_alias") != std::string::npos) // aliases
        {
            ParseAlias(lineData);
            mLastParsedType = LastElement::LINE_ALIAS;
        } 
        else if (ToLower(lineData[0]).find("defaults") == 0)
        {
            error = ParseDefaults(lineData, cnt);
            mLastParsedType = LastElement::LINE_DEFAULTS;
        }
        else if (lineData[0][0] == '#')
        {
            if(ToLower(lineData[0]).find("includedir") != std::string::npos)
            {
                DataManager::getInstance()->AppendIncludedir(lineData[1]);
            }
            else if(ToLower(lineData[0]).find("include") != std::string::npos)
            {
                DataManager::getInstance()->AppendInclude(lineData[1]);
            }
            else // comment
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
                    if (mLastAlias)
                        mLastAlias->AppendComment(tmp);
                }
                else if (mLastParsedType == LastElement::LINE_USER)
                {
                    if (mLastUser)
                        mLastUser->AppendComment(tmp);
                }
                else if (mLastParsedType == LastElement::LINE_DEFAULTS)
                {
                    if (mLastDefaults)
                        mLastDefaults->AppendComment(tmp);
                }
                else
                {
                    DataManager::getInstance()->AppendMainComment(tmp);
                }
            }
        }
        else if (lineData[0][0] == '%' || 
                (DataManager::getInstance()->GetAliasByName(lineData[0]) != NULL && 
                    (DataManager::getInstance()->GetAliasByName(lineData[0])->GetType() == AliasType::USER_ALIAS))) // groups
        {
            error = ParseUser<true>(lineData, cnt);
            mLastParsedType = LastElement::LINE_USER;
        }
        else
        {
            error = ParseUser<false>(lineData, cnt);
            mLastParsedType = LastElement::LINE_USER;
        } 
    }
    else
    {
        switch(mLastParsedType)
        {
            case LastElement::LINE_ALIAS:
                ParseAlias(lineData, mLastAlias, mNextLine);
                break;
            case LastElement::LINE_DEFAULTS:
                error = ParseDefaults(lineData, cnt, mLastDefaults);
                break;
            case LastElement::LINE_USER:
                error = ParseUser<false>(lineData, cnt, mLastUser);
                break;
        }
    }
    
    mContinue = (line[line.length()-1] == '\\');
    mNextLine = (line[line.length()-2] == ':');
    return error;
}

//------------------------------------------------------------------------------

std::string Parser::ParseDefaults(std::vector<std::string> defaultData, unsigned line, DefaultsData* defaults)
{
    DefaultsType type = DefaultsType::ALL_DEFAULTS;
    DefaultsSign sign = DefaultsSign::NONE;
    int currElem = defaults ? 0 : 1;
    std::string param;
    std::string values;
    std::string owner;
    
    for (std::string elem : defaultData)
    {
        if (elem.find(",") != std::string::npos)
        {
            std::stringstream ss;
            ss << "Parser error: Line "
               << line << "\n"
               << "Multiple params for one default entry\n"
               << "Not implemented yet";
            
            return ss.str();
        }
    }
    
    if (!defaults)
    {
        // check type
        if(ToLower(defaultData[0]) != "defaults")
        {
            unsigned len = std::string("defaults").size();
            type = GetDefaultsType(defaultData[0].substr(len, 1));
            owner = defaultData[0].substr(len + 1, std::string::npos);
        }

        /*
        * Defaults param
        *    [0]    [1]
        * Defaults param = value
        *    [0]    [1] [2]   [3]
        * Defaults param= value
        *    [0]    [1]      [2]
        * Defaults param =value
        *    [0]    [1]     [2]
        * Defaults param=value
        *    [0]        [1]
        *
        * Type is all
        */    

        if (defaultData[currElem].find("=") != std::string::npos && defaultData[currElem].length() > 2)
        {
            if(defaultData[currElem].back() == '=')
            {            
                if (defaultData[currElem].back() == '+')
                {
                    sign = DefaultsSign::APPEND;
                    param = defaultData[currElem].substr(0, defaultData[currElem].size() - 2);
                }            
                else if (defaultData[currElem].back() == '-')
                {
                    sign = DefaultsSign::REMOVE;
                    param = defaultData[currElem].substr(0, defaultData[currElem].size() - 2);
                }
                else
                {                
                    sign = DefaultsSign::ASSIGN;
                    // defaults param= ..., just remove =
                    param = defaultData[currElem].substr(0, defaultData[currElem].size() - 1);
                }
                currElem++;
                values = defaultData[currElem];
            }
            else
            {
                // Default param=val
                std::vector<std::string> tmp = Split(defaultData[currElem], "=");
                if (tmp[0].back() == '+')
                {
                    sign = DefaultsSign::APPEND;
                    param = tmp[0].substr(0, defaultData[currElem].size() - 1);                
                }
                else if (tmp[0].back() == '-')
                {
                    sign = DefaultsSign::REMOVE;
                    param = tmp[0].substr(0, defaultData[currElem].size() - 1);                
                }
                else
                {
                    sign = DefaultsSign::ASSIGN;
                    param = tmp[0];
                }
                values = tmp[1];
            }
        }    
        else if(defaultData.size() == 2)
        {
            // Default param
            param = defaultData[currElem];
            if (param[0] == '!')
            {
                sign = DefaultsSign::NEG;
                param = param.substr(1, param.size());
            }
        }
        else if(defaultData[currElem+1].find("=") != std::string::npos && defaultData[currElem+1].length() <= 2)
        {
            if (defaultData[currElem+1] [0] == '+')
            {
                sign = DefaultsSign::APPEND;
            }
            else if (defaultData[currElem+1] [0] == '-')
            {
                sign = DefaultsSign::REMOVE;
            }
            else // '='
            {
                sign = DefaultsSign::ASSIGN;
            }

            // Defaults param = value
            param = defaultData[currElem];
            currElem += 2;
            values = defaultData[currElem];
        }
        else
        {
             // Defaults param =value_list
            param = defaultData[currElem];
            currElem++;
            if (defaultData[currElem][0] == '+')
            {
                sign = DefaultsSign::APPEND;
                values = defaultData[currElem].substr(2, defaultData[currElem].size());
            }
            else if (defaultData[currElem][0] == '-')
            {
                sign = DefaultsSign::REMOVE;
                values = defaultData[currElem].substr(2, defaultData[currElem].size());
            }
            else // '='
            {
                sign = DefaultsSign::ASSIGN;
                values = defaultData[currElem].substr(1, defaultData[currElem].size());
            }
        }
        currElem++;
    }
    
    bool hasComment = false;
    for(int i = currElem; i < defaultData.size(); i++)
    {
        if (defaultData[i][0] == '#')
        {
            hasComment = true;
            currElem = i;
            break;
        }
        values += " " + defaultData[i];
    }
    
    if(values[0] == '\"')
    {
        values = values.substr(1, values.size());
    }
    if (values[values.length()-1] == '\"')
    {
        values = values.substr(0, values.size()-1);  
    }
    
    if (!defaults)
    {
        DataManager::getInstance()->AddDefaults(type, owner, param, values, sign, true);
        mLastDefaults = DataManager::getInstance()->GetLastDefaults();
    }
    else
    {
        defaults->SetValues(defaults->GetValues() + " " + values);
    }
    
    if (hasComment)
    {
        for(int i = currElem; i < defaultData.size(); i++)
        {
            std::string tmp = defaultData[i];
            mLastDefaults->AppendComment(tmp);
        }
    }
    
    return "";
}

//------------------------------------------------------------------------------

template<bool isGroup>
std::string Parser::ParseUser(std::vector<std::string> userData, unsigned line, UserData* user)
{
    
    if(userData.size() < 2) // minimal size of user
    {
        std::stringstream ss;
        
        ss << "Parsing error: Line " 
           << line 
           << ":\n" 
           << userData[0];
        return ss.str();
    }
    
    std::string name = "";
    std::string location = "";
    std::string runAs = "";
    std::list<std::string> cmds; 
    unsigned currentElement = 0;
    bool isSystemGroup = userData[0][0] == '%';
        
    if (!user)
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
         *    [0]       [1]         [2]       [3+]*/
        if (isGroup)
        {
            if(isSystemGroup)
            {
                userData[currentElement].erase(
                                    std::find(
                                        userData[currentElement].begin(), 
                                        userData[currentElement].end(), 
                                        '%')); // we don't need to have this symbol in name
            }    
        }

        name = userData[currentElement];
        location = "";
        runAs = "";
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
                if(tmp.size() < 2)
                {
                    std::stringstream ss;

                    ss << "Parsing error: Line " 
                       << line 
                       << ":\n" 
                       << "not enough elements"
                       << ":\n" 
                       << userData[currentElement];
                    return ss.str();
                }
                
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
    }
    bool hasComment = false;
    
    std::string tmp = "";
    // iterate commands and add to vec
    for(int i = currentElement; i < userData.size(); i++)
    {
        tmp += userData[i];
        if (tmp[tmp.length()-1] == ',')
        {
            cmds.push_back(tmp.substr(0, tmp.length()-1));
            tmp = "";
        }
        else
        {
            tmp += " ";
        }
        
        if (tmp[0] == '#')
        {
            hasComment = true;
            currentElement = i;
            break;
        }
    }
    cmds.push_back(tmp);
    
    if (!user)
    {
        DataManager::getInstance()->AddUser(name, location, runAs, cmds, true, isGroup, isSystemGroup);
        mLastUser = DataManager::getInstance()->GetLastUser();

        if (hasComment)
        {
            for(int i = currentElement; i < userData.size(); i++)
            {
                std::string tmp = userData[i];
                mLastUser->AppendComment(tmp);
            }
        }
    }
    else
    {
        std::list<std::string> cmd = user->GetCmds();
        for (std::string elem : cmds)
        {
            cmd.push_back(elem);
        }
        user->SetCmdsString(cmd);
        if (hasComment)
        {
            for(int i = currentElement; i < userData.size(); i++)
            {
                std::string tmp = userData[i];
                mLastUser->AppendComment(tmp);
            }
        }
    }
    
    return "";
}

//------------------------------------------------------------------------------

void Parser::ParseAlias(std::vector<std::string> aliasData, AliasData* prevAlias, bool nextLine)
{
    AliasType aliasType = (prevAlias ? prevAlias->GetType() : GetAliasType(aliasData[0]));
    
    std::string aliasName = "";
    if(nextLine) aliasName = aliasData[0];
    else aliasName = (prevAlias) ? prevAlias->GetName() : aliasData[1];
    
    std::list<std::string> empty = {};
    std::list<std::string> aliasValues = (prevAlias && !nextLine) ? prevAlias->GetValues() : empty;
    
    unsigned currentElement = 0;
    bool hasComment = false;
    
    int i = 3;
    if(nextLine) i = 2;
    else if(prevAlias) i = 0;
            
    
    for (i; i < aliasData.size(); i++)
    {
        std::string tmp = aliasData[i];
        if (tmp[tmp.length()-1] == '\\')
        {
            tmp = tmp.substr(0, tmp.length()-1);
        }
        if (tmp[tmp.length()-1] == ':')
        {
            tmp = tmp.substr(0, tmp.length()-1);
        }
        if (tmp[tmp.length()-1] == ',')
        {
            tmp = tmp.substr(0, tmp.length()-1);
        }
        if (tmp[0] == '#')
        {
            hasComment = true;
            currentElement = i;
            break;
        }
        
        if (tmp != "")
        {
            aliasValues.push_back(tmp);
        }
    }
    
    if (prevAlias && !nextLine)
    {   
        prevAlias->SetValues(aliasValues);
    }
    else
    {
        DataManager::getInstance()->AddAlias(aliasName, aliasType, aliasValues, true);
    }
    mLastAlias = DataManager::getInstance()->GetLastAlias();
    
    if (hasComment)
    {
        for(int i = currentElement; i < aliasData.size(); i++)
        {
            std::string tmp = aliasData[i];
            mLastUser->AppendComment(tmp);
        }
    }
}

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

DefaultsType Parser::GetDefaultsType(std::string str)
{
    std::string type = ToLower(str);
    if(type == ":")
    {
        return DefaultsType::USER_DEFAULTS;
    }
    else if(type == ">")
    {
        return DefaultsType::RUNAS_DEFAULTS;
    }
    else if(type == "@")
    {
        return DefaultsType::HOST_DEFAULTS;
    }
    else //if(ToLower(str) == "!")
    {
        return DefaultsType::CMDS_DEFAULTS;
    }
}

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

    std::string Parser::PrepareToSave()
    {
        std::stringstream ss;
                
        for(std::string line : DataManager::getInstance()->GetMainComment())
        {
            ss << "# "
               << line
               << std::endl;
        }
        
        ss << std::endl;
        
        for (std::string includedir : DataManager::getInstance()->GetIncludedirs())
        {
            ss << "#includedir "
               << includedir
               << std::endl;
        }
        for(std::string include : DataManager::getInstance()->GetIncludes())
        {
            ss << "#include "
               << include
               << std::endl;
        }
        
        ss << std::endl;
        
        for (DefaultsData* defaults : DataManager::getInstance()->GetDefaultses())
        {
            ss << "Defaults" << defaults->GetTypeToFile()
               << ((defaults->GetType() != DefaultsType::ALL_DEFAULTS) ? defaults->GetOwner() : "") << " "
               << ((defaults->GetSign() == DefaultsSign::NEG) ? "!" : "")
               << g_DefaultsParamNames[static_cast<int>(defaults->GetParam())];
            
            if (!defaults->GetValues().empty())
            {
                switch (defaults->GetSign())
                {
                    case DefaultsSign::APPEND:
                        ss << " += ";
                        break;
                    case DefaultsSign::ASSIGN:
                        ss << " = ";
                        break;
                    case DefaultsSign::REMOVE:
                        ss << " -= ";
                        break;
                }
                
                bool multiple = defaults->GetValues().find(' ') != std::string::npos;
                if (multiple)
                {
                    ss << "\"";
                }
                ss << defaults->GetValues()
                   << (multiple ? "\"\n" : "\n");
            }
            
            ss << std::endl;
            
            if (!defaults->GetComment().empty())
            {
                for(std::string line : defaults->GetComment())
                {
                    ss << "# " << line << std::endl;
                }
                ss << std::endl;
            }
        }
        
        ss << std::endl << std::endl;
        
        for (AliasData* alias : DataManager::getInstance()->GetAliases())
        {
            ss << alias->GetTypeToFile() << " "
               << alias->GetName() << " = "
               << alias->GetValuesString() << std::endl;
            
            if (!alias->GetComment().empty())
            {
                for(std::string line : alias->GetComment())
                {
                    ss << "# " << line << std::endl;
                }
                ss << std::endl;
            }
        }
        
        ss << std::endl << std::endl;
        
        for (UserData* user : DataManager::getInstance()->GetUsers())
        {
            if(user->IsSysGroup())
            {
                ss << "%";
            }
            
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
                for (std::string line : user->GetComment())
                {
                    ss << "# " << line << std::endl; 
                }
                
                ss  << std::endl;
            }
        }
        
        return ss.str();
    }
    
