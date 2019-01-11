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


void MainWindow::PrepareAliasTab(GtkWidget* notebook)
{
    // Aliases
    // aliasName, aliasType, aliasValues
    GtkWidget* treeViewAlias   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
    GtkTreeViewColumn* columnATypes = gtk_tree_view_column_new_with_attributes(
                                                                        "Type", // column title
                                                                        renderer, // GtkCellRenderer
                                                                        NULL); // end of list  
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewAlias),
                                               -1,      
                                               "Type",  
                                               renderer,
                                               "text", 
                                               AliasCols::COL_TYPE,
                                               NULL);  
    renderer = gtk_cell_renderer_text_new ();    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewAlias),
                                               -1,      
                                               "Name",  
                                               renderer,
                                               "text", 
                                               AliasCols::COL_NAME,
                                               NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewAlias),
                                               -1,      
                                               "Value",  
                                               renderer,
                                               "text", 
                                               AliasCols::COL_VALUE,
                                               NULL);   
}


void MainWindow::PrepareAliases()
{
    GtkWidget* treeView   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkTreeIter iter;
    
    GtkListStore* store = gtk_list_store_new(
                                            3, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING);
    for (AliasData* elem : DataManager::getInstance()->GetAliasesByValue(""))
    {
        gtk_list_store_append(store, &iter);
        
        std::string type = elem->GetTypeString();
        std::string name = elem->GetName();
        std::string val  = elem->GetValuesString();
        
        gtk_list_store_set (store, &iter,
                      AliasCols::COL_TYPE, type.c_str(),
                      AliasCols::COL_NAME, name.c_str(),
                      AliasCols::COL_VALUE, val.c_str(),
                      -1);
     
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(store));
}
