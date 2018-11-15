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
#include <vector>

class Parser {
public:
    static Parser* getInstance();
    void ParseLine(std::string line);
    
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

};

#endif /* PARSER_H */

