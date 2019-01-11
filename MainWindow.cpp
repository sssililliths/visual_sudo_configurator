/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.cpp
 * Author: sssililliths
 * 
 */

#include <string>
#include <gtk/gtk.h>
#include "MainWindow.h"
#include "FileManager.h"

void OnClickOpenMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    FileManager* fileManager = FileManager::getInstance();
    fileManager->LoadData();
    MainWindow::getInstance()->ShowData();
}

void OnClickSaveMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    FileManager* fileManager = FileManager::getInstance();
    fileManager->SaveData();
}


void OnClickBtnRemoveAlias(GtkWidget *btn, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkTreeModel* model;
    
    selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
    gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                 &model,
                                 &iter);
    
    if (isSelected)
    {
        gchar* data;
        gtk_tree_model_get (model, &iter,
                           AliasCols::COL_NAME, &data,
                           -1);

        std::stringstream ss;
        ss << data;
        DataManager::getInstance()->RemoveAlias(ss.str());
        MainWindow::getInstance()->ShowData();
    }
}


void OnClickBtnRemoveUser(GtkWidget *btn, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkTreeModel* model;
    
    selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
    gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                 &model,
                                 &iter);
    
    if (isSelected)
    {
        gchar* data;
        gtk_tree_model_get (model, &iter,
                           UserCols::COL_NAME, &data,
                           -1);

        std::stringstream ss;
        ss << data;
        DataManager::getInstance()->RemoveUser(ss.str());
        MainWindow::getInstance()->ShowData();
    }
}


MainWindow* MainWindow::mInstance = 0;

MainWindow::MainWindow()
{
    mBuilder = gtk_builder_new ();
    
    std::string filename = "./mainWindow";
    
    GError *error = NULL;
    if (mBuilder && gtk_builder_add_from_file (mBuilder, filename.c_str(), &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return;
    }
    
    mWindow   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndAppWindow"));
    GtkWidget* notebook = GTK_WIDGET(gtk_builder_get_object(mBuilder, "ntbDataCategories"));
    PrepareTabs(notebook);
}

MainWindow::~MainWindow()
{
}

MainWindow* MainWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new MainWindow();
    }

    return mInstance;
}

void MainWindow::ShowWindow()
{    
    GtkWidget* menuOpen  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiOpen"));
    GtkWidget* menuSave  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiSave"));
    GtkWidget* treeViewAlias   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkWidget* treeViewUser   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvUserData"));
    GtkWidget* buttonAliasAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasAdd"));
    GtkWidget* buttonAliasEdit  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasModify"));
    GtkWidget* buttonUserAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserAdd"));
    GtkWidget* buttonUserEdit  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserModify"));
    GtkWidget* buttonAliasRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasRemove"));
    GtkWidget* buttonUserRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserRemove"));
        
    g_signal_connect (mWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (menuOpen, "activate", G_CALLBACK (OnClickOpenMenuItem), NULL);
    g_signal_connect (menuSave, "activate", G_CALLBACK (OnClickSaveMenuItem), NULL);
    g_signal_connect (buttonAliasAdd, "clicked", G_CALLBACK (OnClickBtnAddAlias), NULL);
    g_signal_connect (buttonUserAdd, "clicked", G_CALLBACK (OnClickBtnAddUser), NULL);
    g_signal_connect (buttonAliasEdit, "clicked", G_CALLBACK (OnClickBtnModifyAlias), treeViewAlias);
    g_signal_connect (buttonUserEdit, "clicked", G_CALLBACK (OnClickBtnModifyUser), treeViewUser);
    g_signal_connect (buttonAliasRemove, "clicked", G_CALLBACK (OnClickBtnRemoveAlias), treeViewAlias);
    g_signal_connect (buttonUserRemove, "clicked", G_CALLBACK (OnClickBtnRemoveUser), treeViewUser);
    
    gtk_widget_show( mWindow );
    gtk_main();
}

void MainWindow::PrepareTabs(GtkWidget* notebook)
{
    PrepareAliasTab(notebook);
    PrepareUserTab(notebook);
}

void MainWindow::ShowData()
{    
    PrepareAliases();
    PrepareUsers();
}
