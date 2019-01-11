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
#include "MainWindow.h"
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
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(MainWindow::getInstance()->GetWindow()),
                                      action,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Open",
                                      GTK_RESPONSE_OK,
                                      NULL);
    
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK)
    {        
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        std::fstream fs;
        fs.open (gtk_file_chooser_get_filename (chooser), std::fstream::in);
        
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
    gtk_widget_destroy (dialog);
}


void FileManager::SaveData()
{
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    GtkWidget *dialog = gtk_file_chooser_dialog_new ("Save File",
                                      GTK_WINDOW(MainWindow::getInstance()->GetWindow()),
                                      action,
                                      "_Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "_Save",
                                      GTK_RESPONSE_OK,
                                      NULL);
    
    
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK)
    {        
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        std::fstream fs;

        fs.open (gtk_file_chooser_get_filename (chooser), std::fstream::out);
        if (fs.good())
        {
            fs << Parser::getInstance()->PrepareToSave();
            
            fs.close();
        }
        else
        {
            //todo: error opening file
        }
    }
    gtk_widget_destroy (dialog);
}

