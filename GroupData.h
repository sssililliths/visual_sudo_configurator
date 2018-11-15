/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupData.h
 * Author: sssililliths
 *
 */

#ifndef GROUPDATA_H
#define GROUPDATA_H

#include <string>
#include <list>

class GroupData {
public:
    GroupData();
    ~GroupData();
private:
    std::string mName;
    std::list<std::string> mUsers;
    std::list<std::string> mCommands;
    std::list<std::string> mTerminals;
    std::string mAs;
};

#endif /* GROUPDATA_H */

