/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.h
 * Author: sssililliths
 *
 */

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <gtk/gtk.h>

class MainWindow 
{
private:
    MainWindow();
    ~MainWindow();
    void PrepareTabs(GtkWidget* notebook);
    void PrepareAliases();

public:
    static MainWindow* getInstance();
    void ShowWindow();
    void ShowData();
    
private:
    static MainWindow* mInstance;    
    GtkBuilder* mBuilder;
};

#endif /* WINDOWMANAGER_H */

