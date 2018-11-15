/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileManager.h
 * Author: sssililliths
 *
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>

class FileManager 
{
private:
    FileManager();
    ~FileManager();

public:
    static FileManager* getInstance();
    void LoadData();
    void ParseFile();
    
private:
    static FileManager* mInstance;
    std::string mFileData;
};

#endif /* FILEMANAGER_H */

