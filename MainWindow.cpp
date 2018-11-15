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
#include <gtk-2.0/gtk/gtkmenuitem.h> 
#include "MainWindow.h"
#include "FileManager.h"
#include "DataManager.h"

void OnClickOpenMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    FileManager* fileManager = FileManager::getInstance();
    fileManager->LoadData();
    MainWindow::getInstance()->ShowData();
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
    GtkWidget* window   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndAppWindow"));
    GtkWidget* notebook = GTK_WIDGET(gtk_builder_get_object(mBuilder, "ntbDataCategories"));
    GtkWidget* menuOpen  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiOpen"));
    
    PrepareTabs(notebook);
    
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (menuOpen, "activate", G_CALLBACK (OnClickOpenMenuItem), NULL);

    gtk_widget_show( window );
    gtk_main();
}

void MainWindow::PrepareTabs(GtkWidget* notebook)
{
    GtkTreeIter iter;
    GtkWidget* treeView   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
    GtkTreeViewColumn* columnTypes = gtk_tree_view_column_new_with_attributes(
                                                                        "Type", // column title
                                                                        renderer, // GtkCellRenderer
                                                                        NULL); // end of list    
    GtkTreeViewColumn* columnNames = gtk_tree_view_column_new_with_attributes(
                                                                        "Name", // column title
                                                                        renderer, // GtkCellRenderer
                                                                        NULL); // end of list    
    GtkTreeViewColumn* columnValues = gtk_tree_view_column_new_with_attributes(
                                                                        "Value", // column title
                                                                        renderer, // GtkCellRenderer
                                                                        NULL); // end of list    
    GtkListStore* store = gtk_list_store_new(
                                            3, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING);
    
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), columnTypes);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), columnNames);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeView), columnValues);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(store));
}

void MainWindow::ShowData()
{
    PrepareAliases();
}

void MainWindow::PrepareAliases()
{
    GtkWidget* treeView   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkTreeIter iter;
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeView)));
    
    for (AliasData* elem : DataManager::getInstance()->GetAliasesByValue(""))
    {
        const gchar *type = elem->GetTypeString().c_str();
        const gchar *name = elem->GetName().c_str();
        const gchar *val = elem->GetValuesString().c_str();
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, type,/* 1, name, 2, val,*/ -1);
    }
}
