/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsTabWindowManager.cpp
 * Author: root
 * 
 */

#include <string>
#include <gtk/gtk.h>
#include "MainWindow.h"


void MainWindow::PrepareDefaultsTab(GtkWidget* notebook)
{
    // Defaultses
    // aliasName, aliasType, aliasValues
    GtkWidget* treeViewDefaults   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvDefaultsData"));
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewDefaults),
                                               -1,      
                                               "Type",  
                                               renderer,
                                               "text", 
                                               DefaultsCols::COL_TYPE,
                                               NULL);  
    renderer = gtk_cell_renderer_text_new ();    
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewDefaults),
                                               -1,      
                                               "Owner",  
                                               renderer,
                                               "text", 
                                               DefaultsCols::COL_OWNER,
                                               NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewDefaults),
                                               -1,      
                                               "Param",  
                                               renderer,
                                               "text", 
                                               DefaultsCols::COL_PARAM,
                                               NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (treeViewDefaults),
                                               -1,      
                                               "Value",  
                                               renderer,
                                               "text", 
                                               DefaultsCols::COL_VALUE,
                                               NULL);   
}


void MainWindow::PrepareDefaults()
{
    GtkWidget* treeView   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvDefaultsData"));
    GtkTreeIter iter;
    
    GtkListStore* store = gtk_list_store_new(
                                            4, 
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING,
                                            G_TYPE_STRING, 
                                            G_TYPE_STRING);
    for (DefaultsData* elem : DataManager::getInstance()->GetDefaultses())
    {
        gtk_list_store_append(store, &iter);
        
        std::string type = elem->GetTypeString();
        std::string owner = elem->GetOwner();
        std::string param = g_DefaultsParamNames[static_cast<int>(elem->GetParam())];
        std::string val  = elem->GetValuesString();
        
        gtk_list_store_set (store, &iter,
                      DefaultsCols::COL_TYPE, type.c_str(),
                      DefaultsCols::COL_OWNER, owner.c_str(),
                      DefaultsCols::COL_PARAM, param.c_str(),
                      DefaultsCols::COL_VALUE, val.c_str(),
                      -1);
     
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeView), GTK_TREE_MODEL(store));
}

