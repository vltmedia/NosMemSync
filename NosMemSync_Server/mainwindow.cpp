#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QHostAddress>
#include <QTextCodec>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
       _socket(this)
{
    ui->setupUi(this);
    // _socket.connectToHost(QHostAddress("127.0.0.1"), 4242);
    _server.listen(QHostAddress::Any, 4242);
connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
       // connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}


void MainWindow::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

         ui->Resultlabel->setText("Retro Arch Files Recieved1");
qDebug() <<  "datas 1";


if(ParseState == "Text"){
    QByteArray datas = sender->readAll();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(datas);
    QString thing = QTextCodec::codecForMib(106)->toUnicode(datas);

    if(thing == "Get RetroArch"){


    }
    ui->Resultlabel->setText(thing);
}



if(ParseState == "SaveFileRetroArch"){
     ui->statusBar->showMessage("RetroArch Files downloading : C:/Users/Justin Jaro/Documents/Temp/TestFiles/tcpdownload.zip");


     QDataStream in(sender);
         in.setVersion(QDataStream::Qt_5_5);
            int blockSize = 22038812;
         if (blockSize == 0) {
             // data to read available
             if ( sender->bytesAvailable() < (int)sizeof(quint16) )
                 return;
             in >> blockSize;
         }
          qDebug() <<  "bytesAvailable";
          qDebug() <<  sender->bytesAvailable();

          qDebug() <<  "blockSize";
          qDebug() <<  blockSize;
         if (sender->bytesAvailable() < blockSize)
             return;

         QByteArray nextByte;
         // read
         in >> nextByte;


         QFile file("C:/Users/Justin Jaro/Documents/Temp/TestFiles/tcpdownload.zip"); // download path

         file.open(QIODevice::WriteOnly);
         file.write(nextByte);
         file.close();





//     sender->waitForReadyRead(30000);
//QByteArray datas = sender->readAll();
//    qDebug() <<  "datas 2";
//   ui->Resultlabel->setText("Retro Arch Files Downloading : ");
//    QFile newDoc("C:/Users/Justin Jaro/Documents/Temp/TestFiles/tcpdownload.zip");

//    if(newDoc.open(QIODevice::WriteOnly)){
//        newDoc.write(datas);
//    }

//    newDoc.close();
       ui->Resultlabel->setText("Retro Arch Files Recieved");
       qDebug() <<  "datas 3";
    ui->statusBar->showMessage("RetroArch Files saved to : C:/Users/Justin Jaro/Documents/Temp/TestFiles/tcpdownload.zip");
    ParseState = "Text";
    qDebug() <<  "datas 4";
}

       for (QTcpSocket* socket : _sockets) {
          if (socket != sender){
           //   socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
          }
      }
}


void MainWindow::on_ResultpushButton_clicked()
{
qDebug() <<  "PoooooP";

}
//void QByteToString(QByteArray Qbytearray, int Codec = 106  ){

//    QString converted = QTextCodec::codecForMib(Codec)->toUnicode(Qbytearray);
//    return converted;

//}

void MainWindow::on_pushButton_clicked()
{
    //QString fpath = FilepathtextEdit.toPlainText();
    QFile file(ui->FilepathtextEdit->toPlainText());
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    ui->FileTextResult->clear();
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        ui->FileTextResult->setText(ui->FileTextResult->text()+line+"\n");
                   qDebug() << "linea: "<<line;
    }

    file.close();


}

void MainWindow::on_SendMessageButton_clicked()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

       for (QTcpSocket* socket : _sockets) {
          if (socket != sender)
              socket->write(QByteArray::fromStdString("What's Up!\n"));
      }
}

void MainWindow::on_pushButton_GetRetroarchFile_clicked()
{

   ParseState = "SaveFileRetroArch";
   ui->statusBar->showMessage("Requested Retro Arch Memory Card. | Status: " + ParseState);
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

       for (QTcpSocket* socket : _sockets) {
          if (socket != sender)
              socket->write(QByteArray::fromStdString("RetroArch"));
      }

}

void MainWindow::SaveQByteArrayToFile(QByteArray BytesArray, QString Filepath){



}
