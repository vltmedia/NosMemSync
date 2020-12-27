#include "mainwindow.h"
#include "tcp_client_a.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Justin Jaro");
       a.setOrganizationDomain("vltbeta.ml");
       a.setApplicationName("NosMemSync_Client");

    //MainWindow w;
    TCP_Client_A w;
    w.show();
    return a.exec();
}
