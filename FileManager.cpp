/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileManager.cpp
 * Author: sssililliths
 * 
 */

#include "FileManager.h"
#include "Parser.h"
#include <sstream>

FileManager* FileManager::mInstance = 0;

FileManager::FileManager() :
    mFileData("")
{
}

FileManager::~FileManager()
{
}

FileManager* FileManager::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new FileManager();
    }

    return mInstance;
}

void FileManager::LoadData()
{
    std::fstream fs;
    
    fs.open ("testSudoersFile", std::fstream::in);
    if (fs.good())
    {
        std::string tmp;
        if (!mFileData.empty())
        {
            mFileData.clear();
        }
        
        while (!fs.eof())
        {
            getline(fs, tmp);
            mFileData.append(tmp);
            Parser::getInstance()->ParseLine(tmp);
        }
        fs.close();
    }
    else
    {
        //todo: error opening file
    }

}

