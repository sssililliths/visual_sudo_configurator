/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AliasEditWindow.h
 * Author: sssililliths
 *
 */

#ifndef ALIASEDITWINDOW_H
#define ALIASEDITWINDOW_H

#include <gtk/gtk.h>
#include "DataManager.h"


void OnClickBtnAddAlias(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyAlias(GtkWidget *btn, gpointer user_data);
    
    
class AliasEditWindow 
{
private:
    AliasEditWindow();
    ~AliasEditWindow();

public:   
    GtkWidget* mWindow;   
    GtkBuilder* mBuilder; 
    
    static AliasEditWindow* getInstance();
    void ShowWindow();
    void ShowData();
    bool PrepareEditWindow();
    bool SetValues(unsigned id);
    bool CheckValidChars(AliasCols elemType, std::string element);
    
private:
    static AliasEditWindow* mInstance; 
    bool mEdit;

    void ConnectEvents();
};

#endif /* ALIASEDITWINDOW_H */

