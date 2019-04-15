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
#include <glib-2.0/gobject/gtype.h>
#include "MainWindow.h"


void MainWindow::PrepareUserTab(GtkWidget* notebook)
{    
    // Users
    // name, location, runAs, cmds
    GtkWidget* treeViewUser  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvUserData"));
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Id",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_ID,
                                               NULL);    
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Name",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_NAME,
                                               NULL);   
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Location",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_LOCATION,
                                               NULL);    
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Run As",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_RUNAS,
                                               NULL);  
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Cmds",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_CMDS,
                                               NULL); 
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "Group",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_IS_GROUP,
                                               NULL); 
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewUser),
                                               -1,      
                                               "System group",  
                                               renderer,
                                               "text", 
                                               UserCols::COL_IS_SYS_GROUP,
                                               NULL); 
}

//------------------------------------------------------------------------------

void MainWindow::PrepareUsers()
{
    GtkWidget* treeView   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvUserData"));
    GtkTreeIter iter;
    
    GtkListStore* store = gtk_list_store_new(
                                            7, 
                                            G_TYPE_STRING,
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING,
                                            G_TYPE_BOOLEAN,
                                            G_TYPE_BOOLEAN);
    for (UserData* elem : DataManager::getInstance()->GetUsers())
    {
        gtk_list_store_append(store, &iter);
        
        std::string name = elem->GetName();
        std::string locations = elem->GetLocation();
        std::string runas = elem->GetRunas();
        std::string cmds = elem->GetCmdsString();
        bool group = elem->IsGroup();
        bool sysGroup = elem->IsSysGroup();
        std::stringstream ss;
        ss << elem->mId;
        
        gtk_list_store_set (store, &iter,
                      UserCols::COL_ID, ss.str().c_str(),
                      UserCols::COL_NAME, name.c_str(),
                      UserCols::COL_LOCATION, locations.c_str(),
                      UserCols::COL_RUNAS, runas.c_str(),
                      UserCols::COL_CMDS, cmds.c_str(),
                      UserCols::COL_IS_GROUP, group,
                      UserCols::COL_IS_SYS_GROUP, sysGroup,
                      -1);
     
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(store));
}

