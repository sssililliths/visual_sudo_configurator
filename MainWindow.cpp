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
#include <gtk-3.0/gtk/gtkmessagedialog.h>
#include <gtk-3.0/gtk/gtkdialog.h>
#include <gtk-3.0/gtk/gtktypes.h>
#include <gtk-3.0/gtk/gtkwindow.h>
#include <gtk-3.0/gtk/gtkbox.h>
#include <gtk-3.0/gtk/gtkcontainer.h>
#include <gtk-3.0/gtk/gtkentry.h>
#include <gtk-3.0/gtk/gtkwidget.h>
#include <gtk-3.0/gtk/gtkbbox.h>
#include <gtk-3.0/gtk/gtkenums.h>
#include <gtk-3.0/gtk/gtkbutton.h>
#include <gtk-3.0/gtk/gtktextview.h>
#include <glib-2.0/glib/gtypes.h>
#include <gtk-3.0/gtk/gtktexttag.h>
#include <gtk-3.0/gtk/gtktextbuffer.h>
#include <gtk-3.0/gtk/gtktextiter.h>
#include "MainWindow.h"
#include "FileManager.h"
#include "DefaultsParams.h"
#include "WindowInterface.h"
#include "WindowInterface.h"

void OnCloseWindow(GtkWidget *btn, gpointer user_data)
{
    gtk_widget_destroy (GTK_WIDGET(user_data));
}

//------------------------------------------------------------------------------

void OnSaveComment(GtkWidget *btn, gpointer user_data)
{
    GtkTextBuffer * buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW(user_data));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buf, &start);
        gtk_text_buffer_get_end_iter(buf, &end);
        gchar* comment = gtk_text_buffer_get_text(buf, &start, &end, true);

        DataManager::getInstance()->SetMainComment(std::string(comment));
        
                GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
                GtkWidget *dialog = gtk_message_dialog_new (
                                    NULL,
                                    flags,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CLOSE,
                                    "Saved");                    
                gtk_window_set_title(GTK_WINDOW(dialog), "Message");
                gtk_dialog_run (GTK_DIALOG (dialog));
                gtk_widget_destroy (dialog);
}

//------------------------------------------------------------------------------

void OnClickEditCommentMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget* window;
    GtkWidget* btnSave;
    GtkWidget* btnCancel;
    GtkWidget* bbBox;
    GtkWidget* txtComment;
    GtkWidget* container;
    GtkTextBuffer* buffer;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Main comment");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    g_signal_connect (window, "destroy", G_CALLBACK (OnCloseWindow), window);
    
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), container);
    
    txtComment = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(container), txtComment, true, true, 1);
    
    bbBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    btnSave = gtk_button_new_with_label("Save");
    btnCancel = gtk_button_new_with_label("Cancel");
    gtk_container_add(GTK_CONTAINER(bbBox), btnSave);
    gtk_container_add(GTK_CONTAINER(bbBox), btnCancel);
    gtk_container_add(GTK_CONTAINER(container), bbBox);
    
    std::string mainComment = DataManager::getInstance()->GetMainCommentStr();
    if (mainComment != "")
    {
        buffer = gtk_text_buffer_new (NULL);
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buffer),
                          mainComment.c_str(),
                          mainComment.length());
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(txtComment), buffer);
    }
    
    g_signal_connect (btnSave, "clicked", G_CALLBACK (OnSaveComment), txtComment);
    g_signal_connect (btnCancel, "clicked", G_CALLBACK (OnCloseWindow), window);
    
    gtk_widget_show_all(window);
}

//------------------------------------------------------------------------------

void OnClickOpenMoreMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    FileManager* fileManager = FileManager::getInstance();
    fileManager->LoadData();
    MainWindow::getInstance()->ShowData();
}

//------------------------------------------------------------------------------

void OnClickSaveMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    FileManager* fileManager = FileManager::getInstance();
    fileManager->SaveData();
}

//------------------------------------------------------------------------------

void OnClickOpenMenuItem (GtkMenuItem *menuitem, gpointer user_data)
{
    if (DataManager::getInstance()->Changed())
    {
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget* dialog = gtk_message_dialog_new (GTK_WINDOW(user_data),
                                         flags,
                                         GTK_MESSAGE_QUESTION,
                                         GTK_BUTTONS_YES_NO,
                                         "Do you want to save existing data?");
        if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_YES)
        {
            OnClickSaveMenuItem(menuitem, user_data);
        }
        
        gtk_widget_destroy (dialog);
        delete DataManager::getInstance();
    }
    
    OnClickOpenMoreMenuItem (menuitem, user_data);
}

//------------------------------------------------------------------------------

void OnClickBtnRemoveAlias(GtkWidget *btn, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkTreeModel* model;
    unsigned id;
    
    selection = gtk_tree_view_get_selection(static_cast<GtkTreeView*>(user_data));
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
        ss >> id;
        DataManager::getInstance()->RemoveAlias(id);
        MainWindow::getInstance()->ShowData();
    }
}

//------------------------------------------------------------------------------

void OnClickBtnRemoveDefaults(GtkWidget *btn, gpointer user_data)
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
        unsigned id;
        gtk_tree_model_get (model, &iter,
                           DefaultsCols::COL_ID, &data,
                           -1);

        std::stringstream ssid;
        ssid << data;
        ssid >> id;
        
        DataManager::getInstance()->RemoveDefaults(id);
        MainWindow::getInstance()->ShowData();
    }
}

//------------------------------------------------------------------------------

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
        unsigned id;
        gtk_tree_model_get (model, &iter,
                           UserCols::COL_ID, &data,
                           -1);

        std::stringstream ss;
        ss << data;
        ss >> id;
        DataManager::getInstance()->RemoveUser(id);
        MainWindow::getInstance()->ShowData();
    }
}

//------------------------------------------------------------------------------

MainWindow* MainWindow::mInstance = 0;

//------------------------------------------------------------------------------

MainWindow::MainWindow()
{
    mBuilder = gtk_builder_new ();
    
    std::string filename = "./mainWindow";
    
    GError *error = NULL;
    //if (mBuilder && gtk_builder_add_from_file (mBuilder, filename.c_str(), &error) == 0)
    if (mBuilder && gtk_builder_add_from_string(mBuilder, gMainWindow.c_str(), gMainWindow.length(), &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return;
    }
    
    mWindow   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "wndAppWindow"));
    GtkWidget* notebook = GTK_WIDGET(gtk_builder_get_object(mBuilder, "ntbDataCategories"));
    PrepareTabs(notebook);
}

//------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    g_object_unref (mBuilder);
}

//------------------------------------------------------------------------------

MainWindow* MainWindow::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new MainWindow();
    }

    return mInstance;
}

//------------------------------------------------------------------------------

void MainWindow::ShowWindow()
{    
    GtkWidget* menuOpen  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiOpen"));
    GtkWidget* menuOpenMore  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiOpenMore"));
    GtkWidget* menuSave  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiSave"));
    GtkWidget* menuComment  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "imiMainComment"));
    GtkWidget* treeViewAlias   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvAliasData"));
    GtkWidget* treeViewUser   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvUserData"));
    GtkWidget* treeViewDefaults   = GTK_WIDGET(gtk_builder_get_object(mBuilder, "trvDefaultsData"));
    GtkWidget* buttonAliasAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasAdd"));
    GtkWidget* buttonAliasEdit  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasModify"));
    GtkWidget* buttonUserAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserAdd"));
    GtkWidget* buttonUserEdit  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserModify"));
    GtkWidget* buttonAliasRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnAliasRemove"));
    GtkWidget* buttonUserRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnUserRemove"));    
    GtkWidget* buttonDefaultsEdit  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnDefaultsModify"));
    GtkWidget* buttonDefaultsRemove  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnDefaultsRemove"));
    GtkWidget* buttonDefaultsAdd  = GTK_WIDGET(gtk_builder_get_object(mBuilder, "btnDefaultsAdd"));
        
    g_signal_connect (mWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (menuOpen, "activate", G_CALLBACK (OnClickOpenMenuItem), NULL);
    g_signal_connect (menuOpenMore, "activate", G_CALLBACK (OnClickOpenMoreMenuItem), NULL);
    g_signal_connect (menuSave, "activate", G_CALLBACK (OnClickSaveMenuItem), NULL);
    g_signal_connect (menuComment, "activate", G_CALLBACK (OnClickEditCommentMenuItem), NULL);
    g_signal_connect (buttonAliasAdd, "clicked", G_CALLBACK (OnClickBtnAddAlias), NULL);
    g_signal_connect (buttonUserAdd, "clicked", G_CALLBACK (OnClickBtnAddUser), NULL);
    g_signal_connect (buttonDefaultsAdd, "clicked", G_CALLBACK (OnClickBtnAddDefaults), NULL);
    g_signal_connect (buttonAliasEdit, "clicked", G_CALLBACK (OnClickBtnModifyAlias), treeViewAlias);
    g_signal_connect (buttonUserEdit, "clicked", G_CALLBACK (OnClickBtnModifyUser), treeViewUser);
    g_signal_connect (buttonDefaultsEdit, "clicked", G_CALLBACK (OnClickBtnModifyDefaults), treeViewDefaults);
    g_signal_connect (buttonAliasRemove, "clicked", G_CALLBACK (OnClickBtnRemoveAlias), treeViewAlias);
    g_signal_connect (buttonUserRemove, "clicked", G_CALLBACK (OnClickBtnRemoveUser), treeViewUser);
    g_signal_connect (buttonDefaultsRemove, "clicked", G_CALLBACK (OnClickBtnRemoveDefaults), treeViewDefaults);
    
    OnClickOpenMenuItem (NULL, NULL);
    
    gtk_widget_show( mWindow );
    gtk_main();
}

//------------------------------------------------------------------------------

void MainWindow::PrepareTabs(GtkWidget* notebook)
{
    PrepareAliasTab(notebook);
    PrepareUserTab(notebook);
    PrepareDefaultsTab(notebook);
}

//------------------------------------------------------------------------------

void MainWindow::ShowData()
{    
    PrepareAliases();
    PrepareUsers();
    PrepareDefaults();
}
