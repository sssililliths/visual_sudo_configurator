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
#include <vector>

enum class LastElement
{
    LINE_EMPTY,
    LINE_USER,
    LINE_ALIAS,
    LINE_COMMENT
};

class Parser {
public:
    static Parser* getInstance();
    void ParseLine(std::string line);
    std::string PrepareToSave();
    
private:
    Parser();
    Parser(const Parser& orig);
    
    std::vector<std::string> Split(std::string str, std::string delim = " ");
    std::string ToLower(std::string str);
    
    AliasType GetAliasType(std::string str);
    void ParseAlias(std::vector<std::string> aliasData);
    template<bool isGroup>
    void ParseUser(std::vector<std::string> aliasData);
    
private:
    static Parser* mInstance;
    
    LastElement mLastParsedType;
    UserData* mLastUser;
    AliasData* mLastAlias;

};

#endif /* PARSER_H */

