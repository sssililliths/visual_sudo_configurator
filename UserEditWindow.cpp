/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UserEditWindow.cpp
 * Author: sssililliths
 * 
 * Created on 11 stycznia 2019, 13:45
 */

#include "UserEditWindow.h"
#include "MainWindow.h"
#include "WindowInterface.h"
#include <gtk/gtk.h>
#include <gtk-3.0/gtk/gtkbuilder.h>
#include <gtk-3.0/gtk/gtktextview.h>

UserEditWindow* UserEditWindow::mInstance = 0;

//------------------------------------------------------------------------------
    
bool haveLetter(char *str);

//------------------------------------------------------------------------------

std::list<std::string> getTreeviewData(GtkTreeModel* model);

//------------------------------------------------------------------------------

void OnCloseUserWindow()
{
    gtk_widget_destroy (UserEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

//------------------------------------------------------------------------------

void OnSaveUserData(GtkWidget *btn, gpointer user_data)
{    
    std::stringstream ss;
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtId"));    
    const gchar* idString = gtk_entry_get_text (GTK_ENTRY(txtId)); 
    ss << idString;
    unsigned id;
    ss >> id;
    
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtName"));    
    const gchar* name = gtk_entry_get_text (GTK_ENTRY(txtName));
    
    GtkWidget* txtLocation  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtHost"));    
    const gchar* location = gtk_entry_get_text (GTK_ENTRY(txtLocation));
    
    GtkWidget* txtRunas  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtRunas"));    
    const gchar* runas = gtk_entry_get_text (GTK_ENTRY(txtRunas));
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "trvCmds"));
    std::list<std::string> valueList = getTreeviewData(gtk_tree_view_get_model(GTK_TREE_VIEW(trvCmds)));
    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtComment"));    
    GtkTextBuffer * buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW(txtComment));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buf, &start);
    gtk_text_buffer_get_end_iter(buf, &end);
    const gchar* comment = gtk_text_buffer_get_text (buf, &start, &end, true);
    
    GtkWidget* chkGroup  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "chkIsGroup"));
    bool isGroup = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(chkGroup));
        
    bool valid = UserEditWindow::getInstance()->CheckValidChars(UserCols::COL_NAME, name);
    valid &= UserEditWindow::getInstance()->CheckValidChars(UserCols::COL_LOCATION, location);
    valid &= UserEditWindow::getInstance()->CheckValidChars(UserCols::COL_RUNAS, runas);
    
    for(std::string element : valueList)
    {
        valid &= UserEditWindow::getInstance()->CheckValidChars(UserCols::COL_CMDS, element);
    }
    if(!valid) return;
    
    bool* edit = static_cast<bool*>(user_data);
    
    if (id && !valueList.empty())
    {
        if(*edit)
        {
            DataManager::getInstance()->ModifyUser(id, std::string(name), location, runas, valueList);
            *edit = false;
        }
        else
        {
            DataManager::getInstance()->AddUser(std::string(name), location, runas, valueList, isGroup, false);
        }
        
        DataManager::getInstance()->SetUserComment((*edit) ? id : DataManager::getInstance()->GetUserId()-1, comment, false);
    }
    else
    {
        // todo message no changes
    }
    
    gtk_widget_destroy (UserEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

//------------------------------------------------------------------------------

void OnAddUserCmd()
{
    GtkWidget* txtCmds  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtCmds"));    
    const gchar * cmd = gtk_entry_get_text (GTK_ENTRY(txtCmds));    
    
    if(cmd != NULL && haveLetter(const_cast<char*>(cmd)))
    {
        GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "trvCmds"));
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

void OnRemoveUserCmd()
{
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "trvCmds"));
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

void OnClickBtnAddUser(GtkWidget *btn, gpointer user_data)
{        
    if (!UserEditWindow::getInstance()->PrepareEditWindow())
    {
        return;
    }
    
    gtk_widget_show( UserEditWindow::getInstance()->mWindow );
    gtk_main();
}

//------------------------------------------------------------------------------

void OnClickBtnModifyUser(GtkWidget *btn, gpointer user_data)
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
                           UserCols::COL_ID, &data,
                           -1);

            std::stringstream ss;
            ss << data;
            ss >> result;
            
            UserEditWindow::getInstance()->PrepareEditWindow(); 
            UserEditWindow::getInstance()->SetValues(result);
        }    
    
    gtk_widget_show( UserEditWindow::getInstance()->mWindow );
    gtk_main();
}

//------------------------------------------------------------------------------

UserEditWindow::UserEditWindow() : mEdit (false)
{
}

//------------------------------------------------------------------------------

UserEditWindow::~UserEditWindow()
{
}

//------------------------------------------------------------------------------

UserEditWindow* UserEditWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new UserEditWindow();
    }

    return mInstance;
}

//------------------------------------------------------------------------------

void UserEditWindow::ConnectEvents()
{
    GtkWidget* btnSave  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnSave"));
    GtkWidget* btnCancel  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnCancel"));
    
    GtkWidget* btnAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAdd"));
    GtkWidget* btnRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnRemove"));
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvCmds"));
    
    g_signal_connect (mWindow, "destroy", G_CALLBACK (OnCloseUserWindow), NULL);    
    g_signal_connect (btnCancel, "clicked", G_CALLBACK (OnCloseUserWindow), NULL);
    g_signal_connect (btnAdd, "clicked", G_CALLBACK (OnAddUserCmd), NULL);
    g_signal_connect (btnRemove, "clicked", G_CALLBACK (OnRemoveUserCmd), NULL);
    g_signal_connect (btnSave, "clicked", G_CALLBACK (OnSaveUserData), &mEdit);
}

//------------------------------------------------------------------------------

bool UserEditWindow::SetValues(unsigned id)
{
    std::stringstream ss;
    UserData* currUser = DataManager::getInstance()->GetUser(id);
    
    GtkWidget* txtId  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtId")); 
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtName"));        
    GtkWidget* txtLocation  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtHost"));    
    GtkWidget* txtRunas  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtRunas"));    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtComment"));    
        
    std::string comment = currUser->GetCommentAsString();
    if (comment != "")
    {
        GtkTextBuffer* buffer;
        buffer = gtk_text_buffer_new (NULL);
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buffer),
                          comment.c_str(),
                          comment.length());
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(txtComment), buffer);
    }
    
    ss << id;
    std::string name = currUser->GetName();
    std::string location = currUser->GetLocation();
    std::string runas = currUser->GetRunas();
    std::string idv = ss.str();
    
    gtk_entry_set_text (GTK_ENTRY(txtId), idv.c_str());
    gtk_entry_set_text (GTK_ENTRY(txtName), name.c_str());
    gtk_entry_set_text (GTK_ENTRY(txtLocation), location.c_str());
    gtk_entry_set_text (GTK_ENTRY(txtRunas), runas.c_str());
    
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
    for (std::string val : currUser->GetCmds())
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set (store, &iter, 0, val.c_str(), -1);
    }
      
    gtk_tree_view_set_model(GTK_TREE_VIEW(trvCmds), GTK_TREE_MODEL(store));
    mEdit = true;
}

//------------------------------------------------------------------------------

bool UserEditWindow::PrepareEditWindow()
{
    mBuilder = gtk_builder_new ();    
    GError *error = NULL;

    if (mBuilder && gtk_builder_add_from_string (mBuilder, gUserWindow.c_str(), gUserWindow.length(), &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return false;
    }
    
    mWindow = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndUserEdit"));
    ConnectEvents();
    
    return true;
}

bool UserEditWindow::CheckValidChars(UserCols elemType, std::string element)
{
    std::string wrongChars = "";
    switch(elemType)
    {
    case UserCols::COL_NAME:
    case UserCols::COL_RUNAS:
    {
        if(element.find('.') != std::string::npos)
        {
            wrongChars.append(". ");
        }
    }
    case UserCols::COL_LOCATION:
    {
        if(element.find(';') != std::string::npos)
        {
            wrongChars.append("; ");
        }
        if(element.find('%') != std::string::npos)
        {
            wrongChars.append("% ");
        }
        if(element.find(' ') != std::string::npos)
        {
            wrongChars.append("space ");
        }
    }
    case UserCols::COL_CMDS:
    {
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
