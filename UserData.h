/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserData.h
 * Author: sssililliths
 *
 */

#ifndef USERDATA_H
#define USERDATA_H

#include <string>
#include <list>

class UserData {
public:
    UserData();
    ~UserData();
private:
    std::string mName;
    std::list<std::string> mGroups;
    std::list<std::string> mCommands;
    std::list<std::string> mTerminals;
    std::string mAs;

};

#endif /* USERDATA_H */

