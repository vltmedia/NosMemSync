#include "tcp_server_a.h"

#include "ui_tcp_server_a.h"
#include <QHostAddress>
#include <QTextCodec>
#include <QFileDialog>
#include  <QtGlobal>


TCP_Server_A::TCP_Server_A(QWidget *parent) : QMainWindow(parent),
    ui (new Ui::TCP_Server_A)
{
    ui-> setupUi (this);

      //ui-> progressLabel-> hide ();

     // QTextCodec :: setCodecForTr (QTextCodec :: codecForName ("GBK"));

      tcpclient = new QTcpSocket (this);
      sendtimes = 0;

      connect (tcpclient, SIGNAL (connected ()), this, SLOT (send ())); // When the connection is successful, start to transfer files
      connect (tcpclient, SIGNAL (bytesWritten (qint64)), this, SLOT (Goonsend (qint64)));

}

TCP_Server_A::~TCP_Server_A()
{
    delete ui;
}

void TCP_Server_A :: send () // Send file header information
{
    bytetowrite = localfile-> size (); // The size of the remaining data
    totalsize = localfile-> size ();

    loadsize = 4 * 1024; // The size of data sent each time

    QDataStream out (& outblock, QIODevice :: WriteOnly);
    QString currentFileName = FileName.right (FileName.size ()-FileName.lastIndexOf ('/')-1);

    out << qint64 (0) << qint64 (0) << currentFileName;

    totalsize += outblock.size (); // The total size is the file size plus the size of the file name and other information
    bytetowrite += outblock.size ();

    out.device ()-> seek (0); // Go back to the beginning of the byte stream to write a qint64 in front, which is the total size and file name and other information size
    out << totalsize << qint64 (outblock.size ());

    tcpclient-> write (outblock); // Send the read file to the socket

    ui->progressLabel-> show ();
    ui->sendProgressBar-> setMaximum (totalsize);
    ui->sendProgressBar-> setValue (totalsize-bytetowrite);
}

void TCP_Server_A :: Goonsend (qint64 numBytes) // Start sending file content
{
    bytetowrite-= numBytes; // Remaining data size
    outblock = localfile-> read (qMin(bytetowrite, loadsize));
    tcpclient-> write (outblock);

    ui-> sendProgressBar-> setMaximum (totalsize);
    ui-> sendProgressBar-> setValue (totalsize-bytetowrite);

    if (bytetowrite == 0) // Send completed
        ui-> sendStatusLabel-> setText (tr ("File sending completed!"));
}


void TCP_Server_A :: on_openPushButton_clicked () // Open the file and get the file name (including path)
{
    ui-> sendStatusLabel-> setText (tr ("Opening file ..."));
    ui-> sendProgressBar-> setValue (0); // Not sent for the first time

    loadsize = 0;
    bytetowrite = 0;
    totalsize = 0;
    outblock.clear ();

    FileName = QFileDialog :: getOpenFileName (this);
    localfile = new QFile (FileName);
    localfile-> open (QFile :: ReadOnly);

    ui->statusbar->showMessage(tr ("File% 1 opened").arg(FileName));
}

void TCP_Server_A :: on_sendPushButton_clicked ()
{
    if (sendtimes == 0) // Only the first time it is sent, it happens when the connection generates the signal connect
    {
        tcpclient-> connectToHost ("127.0.0.1", 4242);
        sendtimes = 1;
    }
    else
        send (); // When sending for the first time, connectToHost initiates the connect signal to call send, and you need to call send after the second time

    ui->statusbar->showMessage("Sending file");
}

void TCP_Server_A :: on_ConnectHost_clicked(){

 tcpclient-> connectToHost ("127.0.0.1", 4242);


}



void TCP_Server_A::on_ConnectHost_2_clicked()
{
    qDebug() << FileName;
     QString currentFileName = "C:/Users/Justin Jaro/Documents/Temp/TestFiles/" + FileName.right (FileName.size ()-FileName.lastIndexOf ('/')-1);
qDebug() << currentFileName;
   QFile::copy(FileName, currentFileName);
}
