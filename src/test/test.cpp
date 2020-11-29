//
// Created by li on 2020/11/29.
//
#include <iostream>
#include "URDriver.h"
#include <QApplication>
#include "MainWindow.h"
int main(int argc,char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}