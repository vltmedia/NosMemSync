#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

#include <QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:QString filename = "";
     QFile file ;




public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QString ParseState = "Text";

public slots:
    void onReadyRead();

    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);

private slots:
    void on_ResultpushButton_clicked();

    void on_pushButton_clicked();

    void SaveQByteArrayToFile(QByteArray BytesArray, QString Filepath);
    void on_SendMessageButton_clicked();

    void on_pushButton_GetRetroarchFile_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer  _server;
    QList<QTcpSocket*>  _sockets;
    QTcpSocket  _socket;
    QFile  localFile ;
};


#endif // MAINWINDOW_H
