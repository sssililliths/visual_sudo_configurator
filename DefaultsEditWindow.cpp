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
#include "WindowInterface.h"


const char *defaultsTypes[] = { "", "USER", "RUNAS", "HOST", "CMDS"};
const char *defaultsMethods[] = { "", "=", "+=", "-=", "!"};

DefaultsEditWindow* DefaultsEditWindow::mInstance = 0;
    

void OnCloseDefaultsWindow()
{
    gtk_widget_destroy (DefaultsEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

void OnSaveDefaultsData(GtkWidget *btn, gpointer user_data)
{
    char* empty = "";
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "cmbType"));
    gchar* activeType = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (cmbType));
    activeType = (activeType == NULL) ? empty : activeType; 
    DefaultsType type = DefaultsType::NUM_TYPES;
    for (int i = 0; i < static_cast<int>(DefaultsType::NUM_TYPES); i++)
    {
        if (strcmp(activeType, defaultsTypes[i]) == 0)
        {
            type = static_cast<DefaultsType>(i);
            break;
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
    
    GtkWidget* cmbMethod  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "cmbMethod"));
    gchar* activeSign = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (cmbMethod));
    activeSign = (activeSign == NULL) ? empty : activeSign; 
    DefaultsSign sign = DefaultsSign::NEG;
    for (int i = 0; i <= static_cast<int>(DefaultsSign::NEG); i++)
    {
        if (strcmp(activeSign, defaultsMethods[i]) == 0)
        {
            sign = static_cast<DefaultsSign>(i);
            break;
        }
    }
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "txtValue"));  
    const gchar* val = gtk_entry_get_text (GTK_ENTRY(trvCmds));
        
    bool valid = DefaultsEditWindow::getInstance()->CheckValidChars(DefaultsCols::COL_OWNER, owner);
    valid &= DefaultsEditWindow::getInstance()->CheckValidChars(DefaultsCols::COL_VALUE, val);
    if(!valid) return;
    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "txtComment"));    
    GtkTextBuffer * buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW(txtComment));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buf, &start);
    gtk_text_buffer_get_end_iter(buf, &end);
    const gchar* comment = gtk_text_buffer_get_text (buf, &start, &end, true);
        
    std::stringstream ss;
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(DefaultsEditWindow::getInstance()->mBuilder, "txtId"));    
    ss << gtk_entry_get_text (GTK_ENTRY(txtId));
    unsigned id;
    ss >> id;
    
    bool* edit = static_cast<bool*>(user_data);
    
    if (activeType && paramType)
    {
        if(*edit)
        {    
            DataManager::getInstance()->ModifyDefaults(id, type, owner, ptype, val, sign);
            DataManager::getInstance()->SetDefaultsComment(id, comment, false);
            *edit = false;
        }
        else
        {
            DataManager::getInstance()->AddDefaults(type, owner, paramType, val, sign, false);
            DataManager::getInstance()->SetDefaultsComment(DataManager::getInstance()->GetDefaultsId()-1, comment, false);
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
}


void OnClickBtnModifyDefaults(GtkWidget *btn, gpointer user_data)
{        
        GtkTreeIter iter;
        GtkTreeModel* model;
        std::string result = "";
        std::stringstream ssid;
        GtkTreeSelection* selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
        gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                     &model,
                                     &iter);    
        unsigned id;
        
        if (isSelected)
        {
            gchar* data;
            gtk_tree_model_get (model, &iter,
                           DefaultsCols::COL_ID, &data,
                           -1);

            ssid << data;
            ssid >> id;
            DefaultsEditWindow::getInstance()->PrepareEditWindow(); 
            DefaultsEditWindow::getInstance()->SetValues(id);
        }
            
    gtk_widget_show( DefaultsEditWindow::getInstance()->mWindow );
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


bool DefaultsEditWindow::SetValues(unsigned id)
{
    std::stringstream ss;
    DefaultsData* currDefaults = DataManager::getInstance()->GetDefaults(id);
    
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtId")); 
    ss << id;
    std::string idv = ss.str();
    gtk_entry_set_text (GTK_ENTRY(txtId), idv.c_str());
    
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbType), static_cast<int>(currDefaults->GetType()));
    
    GtkWidget* cmbMethod  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbMethod"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbMethod), static_cast<int>(currDefaults->GetSign()));
    
    GtkWidget* cmbParameter  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbParameter"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbParameter), static_cast<int>(currDefaults->GetParam()));
    
    GtkWidget* txtOwner  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtOwner"));    
    
    std::string owner = currDefaults->GetOwner();
    gtk_entry_set_text (GTK_ENTRY(txtOwner), owner.c_str());
    
    GtkWidget* txtValue  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtValue"));    
    
    std::string value = currDefaults->GetValues();
    gtk_entry_set_text (GTK_ENTRY(txtValue), value.c_str());
       
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtComment"));    
    
    std::string comment = currDefaults->GetCommentAsString();
    if (comment != "")
    {
        GtkTextBuffer* buffer;
        buffer = gtk_text_buffer_new (NULL);
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buffer),
                          comment.c_str(),
                          comment.length());
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(txtComment), buffer);
    }
    
    mEdit = true;
}


bool DefaultsEditWindow::PrepareEditWindow()
{
    mBuilder = gtk_builder_new ();
    GError *error = NULL;

    if (mBuilder && gtk_builder_add_from_string (mBuilder, gDefaultsWindow.c_str(), gDefaultsWindow.length(), &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return false;
    }
    
    mWindow = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndDefaultsEdit"));
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    GtkWidget* cmbMethod  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbMethod"));
    GtkWidget* cmbParam  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbParameter"));
    
    for (int i = 0; i < static_cast<int>(DefaultsType::NUM_TYPES); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbType), defaultsTypes[i]);
    }
    for (int i = 0; i <= static_cast<int>(DefaultsSign::NEG); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbMethod), defaultsMethods[i]);
    }
    for (int i = 0; i < static_cast<int>(DefaultsParams::NUM_OF_PARAMS); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbParam), g_DefaultsParamNames[i].c_str());
    }
    ConnectEvents();
    
    return true;
}


bool DefaultsEditWindow::CheckValidChars(DefaultsCols elemType, std::string element)
{
    std::string wrongChars = "";
    switch(elemType)
    {
    case DefaultsCols::COL_OWNER:
    {
        if(element.find('.') != std::string::npos)
        {
            wrongChars.append(". ");
        }
    }
    case DefaultsCols::COL_VALUE:
    {
        if(element.find(';') != std::string::npos)
        {
            wrongChars.append("; ");
        }
        if(element.find(',') != std::string::npos)
        {
            wrongChars.append(", ");
        }
        if(element.find('#') != std::string::npos)
        {
            wrongChars.append("# ");
        }
        break;
    }    
    }
    
    if(!wrongChars.empty())
    {
        std::string message = "Found wrong characters at element: " 
                              + element 
                              + "\n "
                              + wrongChars;
        
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *errorDialog = gtk_message_dialog_new (
                                    GTK_WINDOW(MainWindow::getInstance()->GetWindow()),
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    message.c_str());                    
        gtk_window_set_title(GTK_WINDOW(errorDialog), "Wrong characters");
        gtk_dialog_run (GTK_DIALOG (errorDialog));
        gtk_widget_destroy (errorDialog);
        
        return false;
    }
    
    return true;
}
