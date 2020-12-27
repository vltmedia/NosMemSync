#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QHostAddress>
#include <QTextCodec>
#include <QMessageBox>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::connectToServer()
{

    _socket.connectToHost(QHostAddress(ui->HostTextArea->toPlainText()), ui->PortTextArea->toPlainText().toUShort());
    if(_socket.ConnectedState == QAbstractSocket::ConnectedState){
    ui->ServerStatusText_2->setText("CONNECTED");
    ui->ServerStatusText->setText("BROADCASTING");
  ui->statusbar->showMessage("Connected to Server: " + ui->HostTextArea->toPlainText() + " Port: " +ui->PortTextArea->toPlainText() );

    }

    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}



void MainWindow::onReadyRead()
{
    qDebug() << "datas";
    ui->ServerStatusText_2->setText("CONNECTED");


    QByteArray datas = _socket.readAll();
    qDebug() << datas;
    ui->RecievedText->setText(QTextCodec::codecForMib(106)->toUnicode(datas));
//    _socket.write(QByteArray("ok !\n"));
    ReturnData(datas);
}
QString QByteToString(QByteArray Qbytearray, int Codec = 106  ){

    QString converted = QTextCodec::codecForMib(Codec)->toUnicode(Qbytearray);
    return converted;

}
void MainWindow::ReturnData(QString data){

    if(data == "RetroArch"){

        QFile file("C:/Users/Justin Jaro/Documents/Temp/TestFiles/TestFiles_A.zip");
 qDebug() << "Retroarch Saving";
        // If the selected file is valid, continue with the upload
        if (file.exists()) {
            file.open(QIODevice::ReadOnly);
            QByteArray block; // Data that will be sent
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_5);
                out << (quint64)0; // Space for size of data
                out << file.readAll(); // Actual data
                out.device()->seek(0);
                out << (quint64)(block.size() - sizeof(quint64));

            // Send the QByteArray
_socket.write( block);
_socket.waitForBytesWritten(30000);
file.close();
        }

     ui->statusbar->showMessage("Returned RetroArch Files\n");
}

    if(data == "PCSX2"){
     _socket.write(QByteArray("PCSX2 Mem Files\n"));

      ui->statusbar->showMessage("Returned PCSX2 Files\n");
}


}

void MainWindow::on_ConnectServerpushButton_clicked()
{
    connectToServer();
}

void MainWindow::on_pushButton_clicked()
{

              _socket.write(QByteArray(ui->SendTexttextEdit->toPlainText().toLocal8Bit()));



}

void MainWindow::on_comboBoxTest_currentTextChanged(const QString &arg1)
{
    ChoiceTest = arg1;
    qDebug() << arg1;
}

void MainWindow::on_pushButton_2Test_clicked()
{
    ui->label_12->setText(ChoiceTest);
}

void MainWindow::on_RetroArchBrowse_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file("C:/Users/Justin Jaro/Documents/Temp/TestFiles/TestFiles_A.zip");
qDebug() << "Retroarch Saving";
    // If the selected file is valid, continue with the upload
    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QByteArray block; // Data that will be sent
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_5);
            out << (quint64)0; // Space for size of data
            out << file.readAll(); // Actual data
            out.device()->seek(0);
            out << (quint64)(block.size() - sizeof(quint64));
                ui->label_12->setText(QString::number(block.size()));
    }

}
