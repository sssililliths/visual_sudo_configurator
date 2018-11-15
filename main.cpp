/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sssililliths
 *
 */

#include <cstdlib>
#include "MainWindow.h"
#include "FileManager.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    gtk_init(&argc, &argv);
    MainWindow* windowManager = MainWindow::getInstance();
    
    windowManager->ShowWindow();

    return 0;
}

