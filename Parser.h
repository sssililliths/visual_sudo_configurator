/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: sssililliths
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include "AliasData.h"
#include "UserData.h"
#include "DefaultsData.h"
#include <vector>

enum class LastElement
{
    LINE_EMPTY,
    LINE_USER,
    LINE_ALIAS,
    LINE_DEFAULTS,
    LINE_COMMENT
};

class Parser {
public:
    static Parser* getInstance();
    std::string ParseLine(std::string line, unsigned cnt);
    std::string PrepareToSave();
    
private:
    Parser();
    Parser(const Parser& orig);
    
    std::vector<std::string> Split(std::string str, std::string delim = " ");
    std::string ToLower(std::string str);
    
    AliasType GetAliasType(std::string str);
    DefaultsType GetDefaultsType(std::string str);
    void ParseAlias(std::vector<std::string> aliasData);
    template<bool isGroup>
    std::string ParseUser(std::vector<std::string> aliasData, unsigned line);
    void ParseDefaults(std::vector<std::string> defaultData);
    
private:
    static Parser* mInstance;
    
    LastElement mLastParsedType;
    DefaultsData* mLastDefaults;
    UserData* mLastUser;
    AliasData* mLastAlias;
    std::string mMainComment;

};

#endif /* PARSER_H */

