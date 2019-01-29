/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsEditWindow.h
 * Author: root
 *
 */

#ifndef DEFAULTSEDITWINDOW_H
#define DEFAULTSEDITWINDOW_H

#include <gtk/gtk.h>
#include "DataManager.h"


void OnClickBtnAddDefaults(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyDefaults(GtkWidget *btn, gpointer user_data);
    
    
class DefaultsEditWindow 
{
private:
    DefaultsEditWindow();
    ~DefaultsEditWindow();

public:   
    GtkWidget* mWindow;   
    GtkBuilder* mBuilder; 
    
    static DefaultsEditWindow* getInstance();
    void ShowWindow();
    void ShowData();
    bool PrepareEditWindow();
    bool SetValues(DefaultsParams param, DefaultsType type);
    
private:
    static DefaultsEditWindow* mInstance; 
    bool mEdit;

    void ConnectEvents();
};

#endif /* DEFAULTSEDITWINDOW_H */

