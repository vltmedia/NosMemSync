#ifndef TCP_SERVER_A_H
#define TCP_SERVER_A_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <string>

namespace Ui {
class TCP_Server_A;
}

class TCP_Server_A : public QMainWindow
{
    Q_OBJECT
public:
~TCP_Server_A();
    QTcpSocket *tcpclient;

    QFile *localfile;
    QString FileName;

    QByteArray outblock;
    qint64 loadsize;
    qint64 bytetowrite;
    qint64 totalsize;
    QTcpServer  _server;
    QList<QTcpSocket*>  _sockets;
    explicit TCP_Server_A(QWidget *parent = nullptr);
private:

Ui::TCP_Server_A *ui;


    int sendtimes;

private slots:
    void send ();
    void Goonsend (qint64);


    void on_openPushButton_clicked();
    void on_sendPushButton_clicked();
    void on_ConnectHost_clicked();

    void on_ConnectHost_2_clicked();

};




#endif // TCP_SERVER_A_H
