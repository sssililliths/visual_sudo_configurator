/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.h
 * Author: sssililliths
 *
 */

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <gtk/gtk.h>
#include <unistd.h>
#include "DataManager.h"

static std::string currAliasName;
static std::string currUserName;

class MainWindow 
{
private:
    MainWindow();
    ~MainWindow();
    void PrepareTabs(GtkWidget* notebook);
    void PrepareAliasTab(GtkWidget* notebook);
    void PrepareUserTab(GtkWidget* notebook);
    void PrepareGroupTab(GtkWidget* notebook);
    void PrepareAliases();
    void PrepareUsers();
    void PrepareGroups();
    std::string GetTreeviewData(GtkTreeModel* model, int col);

public:
    static MainWindow* getInstance();
    void ShowWindow();
    void ShowData();
    GtkWidget* GetWindow() { return mWindow; }; 
    
private:
    static MainWindow* mInstance;    
    GtkBuilder* mBuilder;
    GtkWidget* mWindow;
};

#endif /* WINDOWMANAGER_H */


void OnClickBtnAddAlias(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyAlias(GtkWidget *btn, gpointer user_data);
void OnClickBtnAddUser(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyUser(GtkWidget *btn, gpointer user_data);
void OnClickBtnAddGroup(GtkWidget *btn, gpointer user_data);
void OnClickBtnModifyGroup(GtkWidget *btn, gpointer user_data);
