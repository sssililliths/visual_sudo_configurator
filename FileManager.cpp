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
    std::fstream fs;
    std::string error = "";
        
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
        fs.open (gtk_file_chooser_get_filename (chooser), std::fstream::in);
    }
    gtk_widget_destroy (dialog);
        
    if (fs.good())
    {
        std::string tmp;
        if (!mFileData.empty())
        {
            mFileData.clear();
        }

        unsigned line = 1;
        while (!fs.eof())
        {
            getline(fs, tmp);
            mFileData.append(tmp);
            error = Parser::getInstance()->ParseLine(tmp, line++);
            if (!error.empty())
            {
                GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
                GtkWidget *errorDialog = gtk_message_dialog_new (
                                    GTK_WINDOW(MainWindow::getInstance()->GetWindow()),
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    error.c_str());                    
                gtk_window_set_title(GTK_WINDOW(errorDialog), "Error");
                gtk_dialog_run (GTK_DIALOG (errorDialog));
                gtk_widget_destroy (errorDialog);
                break;
            }
        }
        fs.close();
    }
    else
    {
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *errorDialog = gtk_message_dialog_new (
                                    GTK_WINDOW(MainWindow::getInstance()->GetWindow()),
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    strerror(errno));                    
        gtk_window_set_title(GTK_WINDOW(dialog), "Error opening file");
        gtk_dialog_run (GTK_DIALOG (errorDialog));
        gtk_widget_destroy (errorDialog);
    }
    
    if (!error.empty())
    {
        delete DataManager::getInstance();
        LoadData();
    }
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

