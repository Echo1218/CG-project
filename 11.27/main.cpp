#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
#include <QDebug>
#include "drawbycommands.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(argc>1)
    {
        DrawByCommands dbc(argv[1],argv[2]);
        dbc.readfile();
        exit(0);
    }
    else
        w.show();

    return a.exec();
}
