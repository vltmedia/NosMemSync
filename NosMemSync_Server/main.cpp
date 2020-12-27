#include "mainwindow.h"
#include"tcp_server_a.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    TCP_Server_A w;
    w.show();
    return a.exec();
}
