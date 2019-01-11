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
#include <gtk/gtk.h>

UserEditWindow* UserEditWindow::mInstance = 0;

    
bool haveLetter(char *str);

std::list<std::string> getTreeviewData(GtkTreeModel* model);


void OnCloseUserWindow()
{
    gtk_widget_destroy (UserEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

void OnSaveUserData(GtkWidget *btn, gpointer user_data)
{    
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtName"));    
    const gchar* name = gtk_entry_get_text (GTK_ENTRY(txtName));
    
    GtkWidget* txtLocation  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtHost"));    
    const gchar* location = gtk_entry_get_text (GTK_ENTRY(txtLocation));
    
    GtkWidget* txtRunas  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtRunas"));    
    const gchar* runas = gtk_entry_get_text (GTK_ENTRY(txtRunas));
    
    GtkWidget* trvCmds  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "trvCmds"));
    std::list<std::string> valueList = getTreeviewData(gtk_tree_view_get_model(GTK_TREE_VIEW(trvCmds)));
    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtComment"));    
    const gchar* comment = gtk_entry_get_text (GTK_ENTRY(txtComment));
    
    GtkWidget* chkGroup  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "chkIsGroup"));
    bool isGroup = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(chkGroup));
    
    if (name && !valueList.empty())
    {
        bool* edit = static_cast<bool*>(user_data);
        if(*edit)
        {
            DataManager::getInstance()->ModifyUser(std::string(name), location, runas, valueList);
            *edit = false;
        }
        else
        {
            DataManager::getInstance()->AddUser(std::string(name), location, runas, valueList, isGroup);
        }
        
        DataManager::getInstance()->SetUserComment(name, comment);
    }
    else
    {
        // todo message no changes
    }
    
    gtk_widget_destroy (UserEditWindow::getInstance()->mWindow);
    MainWindow::getInstance()->ShowData();
}

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


void OnClickBtnAddUser(GtkWidget *btn, gpointer user_data)
{        
    if (!UserEditWindow::getInstance()->PrepareEditWindow())
    {
        return;
    }
    
    gtk_widget_show( UserEditWindow::getInstance()->mWindow );
    gtk_main();
}


void OnClickBtnModifyUser(GtkWidget *btn, gpointer user_data)
{        
        GtkTreeIter iter;
        GtkTreeModel* model;
        std::string result = "";
        GtkTreeSelection* selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
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
            result = ss.str();
        }
        
    UserEditWindow::getInstance()->PrepareEditWindow(); 
    UserEditWindow::getInstance()->SetValues(result);
    
    
    gtk_widget_show( UserEditWindow::getInstance()->mWindow );
    gtk_main();
}


UserEditWindow::UserEditWindow() : mEdit (false)
{
}

UserEditWindow::~UserEditWindow()
{
}

UserEditWindow* UserEditWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new UserEditWindow();
    }

    return mInstance;
}

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


bool UserEditWindow::SetValues(std::string userName)
{
    UserData* currUser = DataManager::getInstance()->GetUser(userName);
    
    GtkWidget* txtName  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtName"));        
    GtkWidget* txtLocation  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtHost"));    
    GtkWidget* txtRunas  = GTK_WIDGET(gtk_builder_get_object(UserEditWindow::getInstance()->mBuilder, "txtRunas"));    
    GtkWidget* txtComment  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "txtComment"));    
    
    std::string comment = currUser->GetComment();
    gtk_entry_set_text (GTK_ENTRY(txtComment), comment.c_str());
    
    std::string name = currUser->GetName();
    std::string location = currUser->GetLocation();
    std::string runas = currUser->GetRunas();
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


bool UserEditWindow::PrepareEditWindow()
{
    mBuilder = gtk_builder_new ();
    std::string filename = "./UserWindow.glade";     
    GError *error = NULL;

    if (mBuilder && gtk_builder_add_from_file (mBuilder, filename.c_str(), &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return false;
    }
    
    mWindow = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndUserEdit"));
    ConnectEvents();
    
    return true;
}

