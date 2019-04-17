/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AliasEditWindow.cpp
 * Author: sssililliths
 * 
 */

#include <gtk/gtk.h>
#include "AliasEditWindow.h"
#include "MainWindow.h"
#include "WindowInterface.h"


AliasEditWindow* AliasEditWindow::mInstance = 0;

//------------------------------------------------------------------------------

const char *aliasTypes[] = { "USER", "RUNAS", "HOST", "CMDS"};
    
//------------------------------------------------------------------------------

bool haveLetter(char *str) 
{ 
    int i = 0; 
    while (str[i]) 
    { 
        if (str[i] != ' ' && 
            str[i] != '\t' && 
            str[i] != '\n' && 
            str[i] != '\0') 
        {
            return true;
        }
        i++; 
    } 
    return false; 
} 

//------------------------------------------------------------------------------

std::list<std::string> getTreeviewData(GtkTreeModel* model)
{    
    GtkTreeIter iter;
    std::list<std::string> result;
    gboolean valid = gtk_tree_model_get_iter_first (model,  &iter);
    while (valid)
    {
        gchar* data;
        gtk_tree_model_get (model, &iter,
                       0, &data,
                       -1);
        
        std::stringstream ss;
        ss << data;
        result.push_back(ss.str());
        
        valid = gtk_tree_model_iter_next (model,  &iter);
    }
    
    return result;
}

//------------------------------------------------------------------------------

void OnCloseWindow()
{
    gtk_widget_destroy (AliasEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

//------------------------------------------------------------------------------

void OnSaveData(GtkWidget *btn, gpointer user_data)
{
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "cmbType"));
    gchar* activeType = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (cmbType));
    AliasType type = AliasType::NUM_TYPES;
    for (int i = 0; i < static_cast<int>(AliasType::NUM_TYPES); i++)
    {
        if (strcmp(activeType, aliasTypes[i]) == 0)
        {
            type = static_cast<AliasType>(i);
        }
    }
    
    std::stringstream ss;
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "txtId"));    
    ss << gtk_entry_get_text (GTK_ENTRY(txtId));
    unsigned id;
    ss >> id;
    
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "txtName"));    
    const gchar* name = gtk_entry_get_text (GTK_ENTRY(txtName));
    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "txtComment"));            
    GtkTextBuffer * buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW(txtComment));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buf, &start);
    gtk_text_buffer_get_end_iter(buf, &end);
    const gchar* comment = gtk_text_buffer_get_text (buf, &start, &end, true);
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "trvCmds"));
    std::list<std::string> valueList = getTreeviewData(gtk_tree_view_get_model(GTK_TREE_VIEW(trvCmds)));
    
    bool valid = AliasEditWindow::getInstance()->CheckValidChars(AliasCols::COL_NAME, name);
    
    for(std::string element : valueList)
    {
        valid &= AliasEditWindow::getInstance()->CheckValidChars(AliasCols::COL_VALUE, element);
    }
    if(!valid) return;
    
    if (activeType && name && !valueList.empty())
    {
        bool* edit = static_cast<bool*>(user_data);
        if(*edit)
        {
            DataManager::getInstance()->ModifyAlias(id, std::string(name), type, valueList);
            DataManager::getInstance()->SetAliasComment(id, comment, false);;
            *edit = false;
        }
        else
        {
            DataManager::getInstance()->AddAlias(std::string(name), type, valueList, false);
            DataManager::getInstance()->SetAliasComment(DataManager::getInstance()->GetAliasId()-1, comment, false);;
        }        
    }
    else
    {
        // todo message no changes
    }
    
    gtk_widget_destroy (AliasEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

//------------------------------------------------------------------------------

void OnAddCmd()
{
    GtkWidget* txtCmds  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "txtCmd"));    
    const gchar * cmd = gtk_entry_get_text (GTK_ENTRY(txtCmds));    
    
    if(cmd != NULL && haveLetter(const_cast<char*>(cmd)))
    {
        GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "trvCmds"));
        GtkTreeIter iter;    
        GtkListStore* store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(trvCmds)));
        
        if(store == NULL)
        {            
            GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
            gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (trvCmds),
                                                       -1,      
                                                       "Values",  
                                                       renderer,
                                                       "text", 
                                                       0,
                                                       NULL);  
            
            store = gtk_list_store_new(1, G_TYPE_STRING);
        }
    
        gtk_list_store_append(store, &iter);
        gtk_list_store_set (store, &iter, 0, cmd, -1);
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(trvCmds), GTK_TREE_MODEL(store));
        
        gtk_entry_set_text (GTK_ENTRY(txtCmds), "");
    }
}

//------------------------------------------------------------------------------

void OnRemoveCmd()
{
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(AliasEditWindow::getInstance()->mBuilder, "trvCmds"));
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkTreeModel* model;
    
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(trvCmds));
    gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                 &model,
                                 &iter);
    
    if (isSelected)
    {
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    }
}

//------------------------------------------------------------------------------

void OnClickBtnAddAlias(GtkWidget *btn, gpointer user_data)
{        
    if (!AliasEditWindow::getInstance()->PrepareEditWindow())
    {
        return;
    }
    
    gtk_widget_show( AliasEditWindow::getInstance()->mWindow );
}

//------------------------------------------------------------------------------

void OnClickBtnModifyAlias(GtkWidget *btn, gpointer user_data)
{        
        GtkTreeIter iter;
        GtkTreeModel* model;
        unsigned result;
        GtkTreeSelection* selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
        gboolean isSelected = gtk_tree_selection_get_selected (selection,
                                     &model,
                                     &iter);    
        if (isSelected)
        {
            gchar* data;
            gtk_tree_model_get (model, &iter,
                           AliasCols::COL_ID, &data,
                           -1);

            std::stringstream ss;
            ss << data;
            ss >> result;
            
            AliasEditWindow::getInstance()->PrepareEditWindow(); 
            AliasEditWindow::getInstance()->SetValues(result);
        }
            
    
    gtk_widget_show( AliasEditWindow::getInstance()->mWindow );
}

//------------------------------------------------------------------------------

AliasEditWindow::AliasEditWindow() : mEdit (false)
{
}

//------------------------------------------------------------------------------

AliasEditWindow::~AliasEditWindow()
{
}

//------------------------------------------------------------------------------

AliasEditWindow* AliasEditWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new AliasEditWindow();
    }

    return mInstance;
}

//------------------------------------------------------------------------------

void AliasEditWindow::ConnectEvents()
{
    GtkWidget* btnSave  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnSave"));
    GtkWidget* btnCancel  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnCancel"));
    
    GtkWidget* btnAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAdd"));
    GtkWidget* btnRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnRemove"));
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvCmds"));
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    
    g_signal_connect (mWindow, "destroy", G_CALLBACK (OnCloseWindow), NULL);    
    g_signal_connect (btnCancel, "clicked", G_CALLBACK (OnCloseWindow), NULL);
    g_signal_connect (btnAdd, "clicked", G_CALLBACK (OnAddCmd), NULL);
    g_signal_connect (btnRemove, "clicked", G_CALLBACK (OnRemoveCmd), NULL);
    g_signal_connect (btnSave, "clicked", G_CALLBACK (OnSaveData), &mEdit);
}

//------------------------------------------------------------------------------

bool AliasEditWindow::SetValues(unsigned id)
{
    AliasData* currAlias = DataManager::getInstance()->GetAlias(id);
    
    std::stringstream ss;    
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtId")); 
    ss << id;
    std::string idv = ss.str();
    gtk_entry_set_text (GTK_ENTRY(txtId), idv.c_str());
    
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    gtk_combo_box_set_active (GTK_COMBO_BOX(cmbType), static_cast<int>(currAlias->GetType()));
    
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtName"));    
    
    std::string name = currAlias->GetName();
    gtk_entry_set_text (GTK_ENTRY(txtName), name.c_str());
    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtComment"));    
    
    std::string comment = currAlias->GetCommentAsString();
    gtk_entry_set_text (GTK_ENTRY(txtComment), comment.c_str());
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvCmds"));
    GtkTreeIter iter;    
    GtkListStore* store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(trvCmds)));
                 
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (trvCmds),
                                                       -1,      
                                                       "Values",  
                                                       renderer,
                                                       "text", 
                                                       0,
                                                       NULL);  
            
    store = gtk_list_store_new(1, G_TYPE_STRING);
    for (std::string val : currAlias->GetValues())
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set (store, &iter, 0, val.c_str(), -1);
    }
      
    gtk_tree_view_set_model(GTK_TREE_VIEW(trvCmds), GTK_TREE_MODEL(store));
    mEdit = true;
}

//------------------------------------------------------------------------------

bool AliasEditWindow::PrepareEditWindow()
{
    mBuilder = gtk_builder_new ();
    GError *error = NULL;

    if (mBuilder && gtk_builder_add_from_string (mBuilder, gAliasWindow.c_str(), gAliasWindow.length(), &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return false;
    }
    
    mWindow = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndAliasEdit"));
    GtkWidget* cmbType  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "cmbType"));
    
    for (int i = 0; i < static_cast<int>(AliasType::NUM_TYPES); i++)
    {
  	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cmbType), aliasTypes[i]);
    }
    ConnectEvents();
    
    return true;
}


bool AliasEditWindow::CheckValidChars(AliasCols elemType, std::string element)
{
    std::string wrongChars = "";
    switch(elemType)
    {
    case AliasCols::COL_NAME:
    {
        if(element.find('.') != std::string::npos)
        {
            wrongChars.append(". ");
        }
    }
    case AliasCols::COL_VALUE:
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
        if(element.find(' ') != std::string::npos)
        {
            wrongChars.append("space ");
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
