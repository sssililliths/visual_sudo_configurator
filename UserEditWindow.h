/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserEditWindow.h
 * Author: sssililliths
 *
 * Created on 11 stycznia 2019, 13:45
 */

#ifndef USEREDITWINDOW_H
#define USEREDITWINDOW_H

#include <gtk/gtk.h>
#include "DataManager.h"


void OnClickBtnAddUser(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyUser(GtkWidget *btn, gpointer user_data);
    
    
class UserEditWindow 
{
private:
    UserEditWindow();
    ~UserEditWindow();

public:   
    GtkWidget* mWindow;   
    GtkBuilder* mBuilder; 
    
    static UserEditWindow* getInstance();
    void ShowWindow();
    void ShowData();
    bool PrepareEditWindow();
    bool SetValues(unsigned id);
    bool CheckValidChars(UserCols elemType, std::string element);
    
private:
    static UserEditWindow* mInstance; 
    bool mEdit;

    void ConnectEvents();
};

#endif /* USEREDITWINDOW_H */

