/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsEditWindow.cpp
 * Author: root
 * 
 */

#include <gtk/gtk.h>
#include "DefaultsEditWindow.h"
#include "MainWindow.h"


const char *defaultsTypes[] = { "", "USER", "RUNAS", "HOST", "CMDS"};

DefaultsEditWindow* DefaultsEditWindow::mInstance = 0;
    

void OnCloseDefaultsWindow()
{
    gtk_widget_destroy (DefaultsEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

void OnSaveDefaultsData(GtkWidget *btn, gpointer user_data)
{
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "cmbType"));
    gchar* activeType = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (cmbType));
    DefaultsType type = DefaultsType::NUM_TYPES;
    for (int i = 0; i < static_cast<int>(DefaultsType::NUM_TYPES); i++)
    {
        if (strcmp(activeType, defaultsTypes[i]) == 0)
        {
            type = static_cast<DefaultsType>(i);
        }
    }
    
    GtkWidget* txtOwner  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "txtOwner"));    
    const gchar* owner = gtk_entry_get_text (GTK_ENTRY(txtOwner));
    
    GtkWidget* cmbParameter  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "cmbParameter"));
    gchar* paramType = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (cmbParameter));
    DefaultsParams ptype = DefaultsParams::NUM_OF_PARAMS;
    for (int i = 0; i < static_cast<int>(DefaultsParams::NUM_OF_PARAMS); i++)
    {
        if(paramType == g_DefaultsParamNames[i])
        {
            ptype = static_cast<DefaultsParams>(i);
            break;
        }
    }
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "txtValue"));  
    const gchar* val = gtk_entry_get_text (GTK_ENTRY(trvCmds));
    
    if (activeType && paramType)
    {
        bool* edit = static_cast<bool*>(user_data);
        if(*edit)
        {
            DataManager::getInstance()->ModifyDefaults(type, owner, ptype, val);
            *edit = false;
        }
        else
        {
            DataManager::getInstance()->AddDefaults(type, owner, paramType, val);
        }
    }
    else
    {
        // todo message no changes
    }
    
    gtk_widget_destroy (DefaultsEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}


void OnClickBtnAddDefaults(GtkWidget *btn, gpointer user_data)
{        
    if (!DefaultsEditWindow::getInstance()->PrepareEditWindow())
    {
        return;
    }
    
    gtk_widget_show( DefaultsEditWindow::getInstance()->mWindow );
    gtk_main();
}


void OnClickBtnModifyDefaults(GtkWidget *btn, gpointer user_data)
{        
        GtkTreeIter iter;
        GtkTreeModel* model;
        std::string result = "";
        std::stringstream ssparam;
        std::stringstream sstype;
        GtkTreeSelection* selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
        gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                     &model,
                                     &iter);    
        if (isSelected)
        {
            gchar* param;
            gchar* type;
            gtk_tree_model_get (model, &iter,
                           DefaultsCols::COL_PARAM, &param,
                           DefaultsCols::COL_TYPE, &type,
                           -1);

            ssparam << param;
            sstype << type;
        }
        
    DefaultsEditWindow::getInstance()->PrepareEditWindow(); 
    DefaultsEditWindow::getInstance()->SetValues(GetParamFromName(ssparam.str()), GetTypeFromName(sstype.str()));
    
    
    gtk_widget_show( DefaultsEditWindow::getInstance()->mWindow );
    gtk_main();
}


DefaultsEditWindow::DefaultsEditWindow() : mEdit (false)
{
}

DefaultsEditWindow::~DefaultsEditWindow()
{
}

DefaultsEditWindow* DefaultsEditWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new DefaultsEditWindow();
    }

    return mInstance;
}

void DefaultsEditWindow::ConnectEvents()
{
    GtkWidget* btnSave  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnSave"));
    GtkWidget* btnCancel  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnCancel"));
    
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    GtkWidget* cmbParam  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbParameter"));
    
    g_signal_connect (mWindow, "destroy", G_CALLBACK (OnCloseDefaultsWindow), NULL);    
    g_signal_connect (btnCancel, "clicked", G_CALLBACK (OnCloseDefaultsWindow), NULL);
    g_signal_connect (btnSave, "clicked", G_CALLBACK (OnSaveDefaultsData), &mEdit);
}


bool DefaultsEditWindow::SetValues(DefaultsParams param, DefaultsType type)
{
    DefaultsData* currDefaults = DataManager::getInstance()->GetDefaults(type, param);
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbType), static_cast<int>(currDefaults->GetType()));
    GtkWidget* cmbParameter  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbParameter"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbParameter), static_cast<int>(currDefaults->GetType()));
    
    GtkWidget* txtOwner  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtOwner"));    
    
    std::string owner = currDefaults->GetOwner();
    gtk_entry_set_text (GTK_ENTRY(txtOwner), owner.c_str());
    
    GtkWidget* txtValue  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtValue"));    
    
    std::string value = currDefaults->GetValues();
    gtk_entry_set_text (GTK_ENTRY(txtValue), value.c_str());
    mEdit = true;
}


bool DefaultsEditWindow::PrepareEditWindow()
{
    mBuilder = gtk_builder_new ();
    std::string filename = "./defaultsWindow.glade";     
    GError *error = NULL;

    if (mBuilder && gtk_builder_add_from_file (mBuilder, filename.c_str(), &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return false;
    }
    
    mWindow = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndDefaultsEdit"));
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    GtkWidget* cmbParam  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbParameter"));
    
    for (int i = 0; i < static_cast<int>(DefaultsType::NUM_TYPES); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbType), defaultsTypes[i]);
    }
    for (int i = 0; i < static_cast<int>(DefaultsParams::NUM_OF_PARAMS); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbParam), g_DefaultsParamNames[i].c_str());
    }
    ConnectEvents();
    
    return true;
}